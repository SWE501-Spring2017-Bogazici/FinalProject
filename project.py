#! /usr/bin/env python
import sys
import Queue 

class Cpu(object):
    def __init__(self, id, freq):
        self.id=id
        self.idle=True        
        self.freq=freq
        self.active_time=0.0
        
    def work(self, task, now):    
        self.idle=False
        task.cpu_service_start=now        
        processing_time=task.cpu_work/self.freq
        task.cpu_service_stop=now+processing_time                
        self.active_time=self.active_time+processing_time
                
class Outdevice(object):
    def __init__(self, id, quantum, sim):
        self.id=id
        self.idle=True
        self.quantum=quantum
        self.active_time=0.0
        self.sim=sim
        
    def work(self, task, now):
        self.idle=False
        if task.remaining_out_work<self.quantum:
            task.outtime=now+task.remaining_out_work
            self.active_time=self.active_time+task.remaining_out_work            
            self.sim.schedule(OutFreeEvent(self.sim, task, task.outtime, self))            
            task.remaining_out_work=0
            task.finished=True                 
        elif task.remaining_out_work==self.quantum:
            task.outtime=now+self.quantum
            self.active_time=self.active_time+self.quantum
            self.sim.schedule(OutFreeEvent(self.sim, task, task.outtime, self))            
            task.remaining_out_work=0
            task.finished=True   
        else:
            task.remaining_out_work=task.remaining_out_work-self.quantum
            self.active_time=self.active_time+self.quantum
            task.outtime=now+self.quantum
            self.sim.schedule(OutFreeEvent(self.sim, task, task.outtime, self))
                                        
class Task(object):
    def __init__(self, id, arrival_time, cpu_work, out_work):
        self.id=id
        self.arrival_time=arrival_time                
        self.cpu_work=cpu_work
        self.out_work=out_work  
        
        self.remaining_out_work=out_work
        self.cpu_service_start=0
        self.cpu_service_stop=0
        self.outtime=0
        
        self.wait_cpu=0
        self.wait_out=0
        self.finished=False
    def __str__(self):
        return str(self.id)
    def __repr__(self):
        return str(self.id)
        
class Event(object):
    def __init__(self, sim, task, time):
        self.sim=sim
        self.task=task
        self.time=time
    
    def yaz(self):
        print str(type(self))+" time:"+str(self.time) + " task:"+str(self.task.id)
        
    def __cmp__(self, other):
        return cmp(self.time, other.time)  

class TaskOutArrivalEvent(Event):     
    def process(self):
        """
        Try getting the first idle output device. Create OutInEvent with that device and this task if successful.
        Otherwise put this task to rrQueue
        """
        out=self.sim.getFirstIdleOut()
        if out is not None:
            event=OutInEvent(self.sim, self.task, self.time, out)
            self.sim.schedule(event)
        else:
            self.sim.add_task_to_rr_queue(self.task)
            
class OutInEvent(Event):
    def __init__(self, sim, task, time, out):
        super(OutInEvent, self).__init__(sim, task, time)
        self.out=out
        
    def process(self):
        """
        Start working on the task with the output device.
        """
        self.out.work(self.task, self.time)
        
    def yaz(self):
        print str(type(self))+" o:"+str(self.out.id)+" time:"+str(self.time) +\
        " task:"+str(self.task.id)+ " rem:"+str(self.task.remaining_out_work) + " fin "+str(self.task.finished)

class OutFreeEvent(Event):
    def __init__(self, sim, task, time, out):
        super(OutFreeEvent, self).__init__(sim, task, time)
        self.out=out    
        
    def process(self):
        """
        If task is finished schedule a TaskFinishedEvent event. Otherwise add the task to rrQueue.
        Also schedules a TaskOutArrivalEvent 
        """
        self.out.idle=True
        if self.task.finished:
            self.sim.schedule(TaskFinishedEvent(self.sim, self.task, self.time))
        else:
            self.sim.add_task_to_rr_queue(self.task)
        
        
        task=self.sim.get_task_from_rr_queue()            
        task.wait_out=task.wait_out+(self.time-task.outtime)
        
#         self.sim.schedule(OutInEvent(self.sim, task, self.time, self.out))
        self.sim.schedule(TaskOutArrivalEvent(self.sim, task, self.time))
        
            
    def yaz(self):
        print str(type(self))+" o:"+str(self.out.id)+" time:"+str(self.time) +\
        " task:"+str(self.task.id)+ " rem:"+str(self.task.remaining_out_work) + " fin "+str(self.task.finished)

class TaskFinishedEvent(Event):
    def process(self):
        pass
#         print "task "+str(self.task.id)+ " finished"
        
class TaskCpuArrivalEvent(Event):    
    def process(self):
        """ When the task arrives, get the first idle cpu, create CpuInEvent with that cpu and self.task.
        If there are no idle cpus put task to sjf queue
        """
        cpu=self.sim.getFirstIdleCpu()
        if cpu is not None:
            event=CpuInEvent(self.sim, self.task, self.time, cpu)
            self.sim.schedule(event)
        else:
            self.sim.add_task_to_sjf_queue(self.task)
    
class CpuInEvent(Event):
    def __init__(self, sim, task, time, cpu):
        super(CpuInEvent, self).__init__(sim, task, time)
        self.cpu=cpu   
        
    def process(self):
        """ update stats, work on the task, schedule a CpuOutEvent """
        self.task.wait_cpu=self.time - self.task.arrival_time
        self.cpu.work(self.task, self.time)
        self.sim.schedule(CpuOutEvent(self.sim, self.task, self.task.cpu_service_stop, self.cpu))    
    
    def __str__(self):
        return "ci:"+str(self.cpu.id)+" t:"+str(self.task.id)+" time:"+str(self.time)
    
class CpuOutEvent(Event):
    def __init__(self, sim, task, time, cpu):
        super(CpuOutEvent, self).__init__(sim, task, time)
        self.cpu=cpu      
        
    def process(self):
        """ If there are tasks waiting in the sjf queue, get the shortest task
            and schedule a CpuInEvent. Otherwise do nothing
        """                
        self.cpu.idle=True
        if not self.sim.sjf_queue.empty():
            task=self.sim.get_task_from_sjf_queue()
            self.sim.schedule(CpuInEvent(self.sim, task, self.time, self.cpu))
        else:
            pass
        
        self.task.outtime=self.time
        event=TaskOutArrivalEvent(self.sim, self.task, self.time)
        self.sim.schedule(event)
        
    def __str__(self):
        return "co:"+str(self.cpu.id)+" t:"+str(self.task.id)+" time:"+str(self.time)
    
class Simulation(object):
    def __init__(self):
        self.cpus=[]
        self.outs=[]
        
        self.time=0         
        
        self.fel=Queue.PriorityQueue()
        
        self.sjf_queue=Queue.PriorityQueue()
        self.rr_queue=Queue.PriorityQueue()

        self.tasks_list=[] 
        
        self.sjf_queue_max_size=0
        self.rr_queue_max_size=0
        self.max_active_cpu_id=0
        self.max_active_out_id=0
        self.average_wait_time=0.0
        self.longest_wait_time=0.0
        self.average_time_spent=0.0
                            
    def addtask(self,task):
        self.tasks_list.append(task)
        
    def addcpu(self,cpu):
        self.cpus.append(cpu)
        
    def addout(self,out):
        self.outs.append(out)
    
    def add_task_to_rr_queue(self, task):
        self.rr_queue.put((task.outtime, task))
        
    def get_task_from_rr_queue(self):
        return self.rr_queue.get(False)[1]
        
    def add_task_to_sjf_queue(self, task):
        self.sjf_queue.put((task.cpu_work, task), False)
        
    def get_task_from_sjf_queue(self):
        return self.sjf_queue.get(False)[1]
        
    def schedule(self, event):
        self.fel.put(event, False)
        
    def getFirstIdleOut(self):
        for out in self.outs:
            if out.idle:
                return out
        return None
        
    def getFirstIdleCpu(self):
        for cpu in self.cpus:
            if cpu.idle:
                return cpu
        return None
    
    def run(self):        
        for task in self.tasks_list:
            self.fel.put(TaskCpuArrivalEvent(self, task, task.arrival_time))
                
        while True:
            try:
                event= self.fel.get(False)                                
                self.time=event.time                
                event.process()

                current_sjf_size= self.sjf_queue.qsize()
                if current_sjf_size>self.sjf_queue_max_size:
                    self.sjf_queue_max_size=current_sjf_size
                    
                current_rr_size= self.rr_queue.qsize()
                if current_rr_size>self.rr_queue_max_size:
                    self.rr_queue_max_size=current_rr_size
                                    
            except Queue.Empty:
                if self.fel.empty():                    
                    break
        
        self.max_cpu_active_time=0
        for cpu in self.cpus:
            if cpu.active_time>self.max_cpu_active_time:
                self.max_cpu_active_time=cpu.active_time
                self.max_active_cpu_id=cpu.id
                
        self.max_out_active_time=0
        for out in self.outs:
            if out.active_time>self.max_out_active_time:
                self.max_out_active_time=out.active_time
                self.max_active_out_id=out.id
        
        grand_total_wait=0.0
        total_time_spent=0.0
        for task in self.tasks_list:
            time_spent= task.outtime-task.arrival_time
            total_time_spent= total_time_spent+time_spent
            total_wait=task.wait_cpu+task.wait_out
            grand_total_wait=grand_total_wait+total_wait
            if total_wait>self.longest_wait_time:
                self.longest_wait_time=total_wait
        self.average_wait_time= grand_total_wait/len(self.tasks_list)
        self.average_time_spent=total_time_spent/len(self.tasks_list)
                
def main(inputFileName, outputFileName):
    """Create a simulation object.
    Read the inputFile.
    Set attributes of the simulation object with the data read.
    Run the simulation.
    Create the outputFile.
    """
    sim=Simulation()
    file = open(inputFileName, "r")
    numcpus= int(file.readline())
    for i in range(numcpus):
        freq= float(file.readline())
        cpu= Cpu(i+1, freq)
        sim.addcpu(cpu)

    numouts= int(file.readline())
    for i in range(numouts):
        quantum= float(file.readline())
        out= Outdevice(i+1, quantum, sim)
        sim.addout(out)

    numtasks= int(file.readline())
    for i in range(numtasks):
        line= file.readline()
        arrtime,cpuwork,outwork=[float(x) for x in line.split()]
        t=Task(i, arrtime, cpuwork, outwork)
        sim.addtask(t)

    file.close()

    sim.run()
    with open(outputFileName,"w") as f:
        f.write(str(sim.sjf_queue_max_size)+"\n")
        f.write(str(sim.rr_queue_max_size)+"\n")
        f.write(str(sim.max_active_cpu_id)+"\n")
        f.write(str(sim.max_active_out_id)+"\n")
        f.write(str(sim.average_wait_time)+"\n")
        f.write(str(sim.longest_wait_time)+"\n")
        f.write(str(sim.average_time_spent)+"\n")
    
    return 0

if __name__ == '__main__':
    args=sys.argv
    inputFileName= args[1]
    outputFileName= args[2]    
    sys.exit(main(inputFileName, outputFileName))    

