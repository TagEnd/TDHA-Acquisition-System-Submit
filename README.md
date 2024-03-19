# TDHA-Acquisition-System-Submit

# TDHA file structure

The dataset file format is shown below:

- The Aggregate folder records the instantaneous current and voltage data when the 7 sets of aggregated household appliances are switched on and off, which are stored in separate files named Aggregation_N.csv (N = {1,2...7}), respectively. The labeling of the switching times of these seven sets of aggregated household appliances is stored in the Event folder.

- The SocketRecord.xlsx file records information about the appliances that were accessed during the measurement of the 7 sets of aggregated appliance data. This file contains 7 worksheets, each of which is corresponding to a set of aggregated household appliance data.

- The Background folder records background current and voltage data in the absence of household appliances being connected. It is mainly used to record the background noise of current and voltage in the absence of household appliances. The folder contains two files: background_5Relay.csv and background_NoRelay.csv.

​				The background_5Relay.csv file records the data in the case where there are no household appliances connected and only relays are connected.

​				The background_NoRelay.csv file records the data in the case where there is no household appliance access and no relay access.

- The remaining folders record instantaneous current and voltage data for various household appliances when switched individually in different on/off states. The names of these folders are a combination of the name of the household appliance and the gear (if the appliance has only one gear, the folder name is the name of the household appliance). Take the folder named "Displayer" as an example:

​				Displayer_N.csv (N = {1,2...7}): Records the instantaneous current and voltage data file when the displayer is switched on/off individually.

​				Displayer_sign_N.csv (N = {1,2...7}): A labeled file that records the switching time of the displayer.

![TDHA2](https://github.com/TagEnd/TDHA-Acquisition-System-Submit/blob/master/TDHA2.svg)

# File data structure

## Data file

- The “DeviceTime” attribute is primarily used for checking file integrity and holds no actual significance.
- The “HomeID“ attribute is used to identify the serial number of the simulated home environment, facilitating future expansion of the dataset.
- The “RecvTime” attribute is used to denote the time of data reception.
- The “Channel” attribute is used to identify the channel of data acquisition (Channel=1 for voltage, Channel=2 for current).
- The “InternalIndex ” attribute is used for internal sorting of data file records.
- The “Rate” attribute is used to denote the number of sampling points per cycle of data.
- The “Value” attribute is used to record the collected data values for each cycle, separated by "|".
- The “Notes” attribute is used for annotating additional information.

## Data labeling files

- The "Time" attribute is used to record the time of the labeled event;

- The "event" attribute is used to record the event that occurred at that time;

  There are two formats for the event attribute in the data annotation file:

  ​		The first is the data annotation format for aggregated electrical appliances (Socket0: 1,Socket1: 1,Socket2: 0,Socket3: 1,Socket4: 1), "Socket%" identifies the number of the appliance plug, "Socket%" identifies whether the appliance connected to the plug is switched on or not. "0/1" identifies whether the appliance connected to the socket is turned on, such as:

  Socket0: 1,**Socket1: 0**,Socket2: 1,Socket3: 1,Socket4: 0 

  ​											To 

  Socket0: 1,**Socket1: 1**,Socket2: 1,Socket3: 1,Socket4: 0 

  Indicates that the appliance connected to socket 1 is turned on;

  ​		The second is a single appliance labeling format (1-1/1-0), "1-1" indicates that the appliance turns on in the No. 1 simulated environment, and "1-0" indicates that the appliance turns off in the No. 1 simulated environment.

## Data annotation

- The mapping from annotation files to data files mainly depends on the “Time ”attribute of the annotation files and the “RecvTime ” attribute of the data files.
