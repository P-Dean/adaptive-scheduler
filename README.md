### Adaptive-Scheduler #

Repository for the Dana Self-Adaptive Scheduler.

## Compile and Run:
REQUIRED: Please ensure the Dana programing langauge has been correctly installed for your deployed environment, a tutorial for setup may be found here: 
*ensure updated rest.dn is used for a single machine*

Within the *adaptive-scheduler* directory, to compile enter the following command:

`dnc .`

OR

`dnc [filename].dn`

## [For a single machine] Within the *adaptive-scheduler* directory enter the following to run:

`dana pal.rest -p [port number for pal.rest] [filename].o`

## [For a cluster of machines] Within the *adaptive-scheduler* directory enter the following to run:

`dana pal.rest ./[filename].o`


ALTERNATIVELY

On a Linux Operating System you may use aliases for starting the Resource Manager [Master] and Node Managers [Workers] nodes:

Access the .\bashrc:
`nano .\bashrc`

Place the following into .\bashrc for:

[Master Node]: `alias resourceManager='cd <YourHomeDirectory>/adaptive-scheduler && dana pal.rest ./ResourceManager.o'`


[Worker Node]: `alias nodeManager='cd <YourHomeDirectory>/adaptive-scheduler && dana pal.rest ./NodeManager.o'`

Rehresh environment variables within the bashrc:
`source ~/.bashrc`

You may now launch a Resource/Node manager by entering the following commands:
Master node: `resourceManager`
Worker node: `nodeManager`

### Submit Applications using TCPClient.dn

## For individual applications:
`dana .\TCPClient.o ~driver-cores <int >= 1 for number of threads> ~driver-me
mory <int >=1 for Gigabytes with apppended g> ~executor-memory <int >=1 for Gigabytes with apppended g> ~executor-cores <int >= 1 for number of threads> ~num-executors <limit for number of executors> ~applica
tion-name <User defined name consiting of char/integers> ~application-dn <dir containing the applicaion.o on the worker nodes>  
~num-partitions <int defining number of task to be created> ~application-data <location of input data for application[Required but not used]>\Input-Data\AliceDTRH.txt`

# For example:
` dana .\TCPClient.o ~driver-cores 1 ~driver-memory 2g ~executor-memory 2g ~executor-cores 2 ~num-executors 2
~application-name AppFG4 ~application-dn Workloads/FG-W-v2/CG-6min.o ~num-partitions 5 ~application-data \Input-Data\AliceDTRH.txt`

The above command will create an Application Master with a reservation of 1 thread and 2 gigabytes of memory, with a maximum of 2 executors allowed to run concurrently across the cluster with
the reservation of 2 threads and 2 gigabytes of memory each. The application to be run is "CG-6min.o", the application will be performed 5 times across executors

## For the submission of a workload[for more detailed information on the format of a Workload see Workloads\README-Workload]:

	 'dana .\TCPClient.o wkld <directory containing [yourWorkload.txt]>'
# For example:
	 'dana .\TCPClient.o wkld .\Workloads\test\TW-FG.txt'

The above command will submit the workload TW-FG.txt from the "test" to the Resource Manager [see Workloads\test\test-V2\TW-FG.txt for an example].
NOTE: Ensure each application in the workload is on a new line and there is no additional whitespace at the end of the .txt  file containing the workload

## Troubleshooting
NodeManagers are failing to deploy executors / executors are failling to connect to the ResouceManager: 
Setting IP addresses - Please ensure the ResouceManager's IP address is present within the first entry of masters.txt exists on all deployed nodes and is correct.
Firewall restrictions - Adaptive scheduler uses the following ports for job/task deployment and telemetry data between management components 2012,2014, 2033, 2021, 3000, 3001, 3010, 3022, 3030, 3040, 3050. In addition, the following port range for application masters/executors 2142-2221 (expand this ip address range wihtin the Nodemanager.dn if more than 80 concurrent clients are required for your deployment)

## Addiitonal information
A more detailed explaination of the dana component compositions avaialble and the adaptive schedulers architecture may be found within previous publications, notably: 

P. Dean and B. Porter, "The Design Space of Emergent Scheduling for Distributed Execution Frameworks," 2021 International Symposium on Software Engineering for Adaptive and Self-Managing Systems (SEAMS), Madrid, Spain, 2021, pp. 186-195, doi: 10.1109/SEAMS51251.2021.00032.
keywords: {Energy consumption;Runtime;Correlation;Processor scheduling;Distributed databases;Dynamic scheduling;Data processing;scheduling;distributed execution frameworks;emergent;self adaptive}, 

# Further Questions
If you require any addiitonal information regarding the adaptive scheduler, the underlying distributed executino frannework, or any issues regardining the setup of this repo, please contact me at: p.dean1@lancaster.ac.uk