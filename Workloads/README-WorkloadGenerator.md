## Synthetic Workload Generation
The following README  details the generation of synthetic workloads for the adaptive-scheduler, upper and lower bounds may be set to generate a workload with properties not seen within the current executor deployed tasks. 

### Files located on the master/worker 

The workloads directory is placed on a worker node and is executed upon the master submitting an application master to the worker and the application master launching the user submitted application (which is either a single or list of workloads which may be found in the CG, FG and, MG directories).

each application within the workload directory is created with the purpose of occupying a CPU thread for a set amount of time in minutes and can be seen within the file name. An example is the file 'CG-6min.o', once launched by an application master’s executor thread the CPU will be reserved by the process for 6 minutes. 

NOTE: the number of partitions within a user submitted request can increase this significantly a thread receives a single CG-6min.o for each partition, therefore 10 partitions and a single thread will take 1 hour, assuming the executor and application master are available at runtime. 

### How to format a workload 

Workloads are created via txt files submitted to the Application Manager before being parsed and passed to the resource manager.

Each workload must follow the set structure to be parsed correctly [Although only application-d, num-partitions, application-data and num-executors are required as default values exist for resource requirements]. 

The structure of a workload may be seen below:

~ is used to separate entries

~driver-cores: The number of cores desired for the Application Master (the AM can operate on a single thread)
~driver-memory: The amount of RAM to be reserved for the Application Master
~executor-memory: The amount of RAM each executor may reserve 
~executor-cores: The number of threads allocated to each executor
~num-executors: The maximum limit on the number of concurrently running executors
~application-name: A user specified entry used for identifying the workload
~application-dn: The dir containing the .o file to be executed by each executor
~num-partitions: The number of tasks to be created, each task will execute the application-dn
~application-data: The input data for the application (synthetic workloads require the entry but do not use the data)

### Complete Workload Example 

~driver-cores 1 ~driver-memory 2g ~executor-memory 2g ~executor-cores 2 ~num-executors 2 ~application-name AppFG4 ~application-dn Workloads/FG-W-v2/CG-6min.o ~num-partitions 5 ~application-data \Input-Data\AliceDTRH.txt

A list may be formed with each application on a newline, once placed in a txt file this will create a workload, and the scheduler will decide the execution order.

# Submitting a Workload #

A workload may be submitted to the resourceManager via two separate methods, in a workload or individually.

The process of submitting a workload [ensure the workload is formatted correctly see above {How to format a workload}].

From within the TCPClient.dn dir issue the following commands:

compile TCPClient.dn:
	dnc TCPClient.dn 

Submit a Workload .txt file:
	 dana .\TCPClient.o wkld <directory containing [yourWorkload.txt]>

E.g.  dana .\TCPClient.o wkld .\Workloads\test\test-v2\TW-FG.txt

The above command will submit the test-V2 workload TW-FG.txt to the Resource Manager.




