<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  -------------------------------------------------
  ![](spacer.gif){width="8" height="1"}Statistics
  -------------------------------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">How to read and interpret RakNet's        |
| statistical data </span>\                                                |
| \                                                                        |
| Statistical data is important for an online game because it lets you see |
| where your traffic bottlenecks are.                                      |
|                                                                          |
| RakPeerInterface provides the structure RakNetStatistics which is        |
| returned by the GetStatistics() function present in RakPeerInterface.    |
| This structure is defined in *Source/RakNetStatistics.h*. The function   |
| StatisticsToString is also provided which will convert these statistics  |
| to a formatted buffer.                                                   |
|                                                                          |
| A running total is kept for the following enumerations                   |
|                                                                          |
| /// How many bytes per pushed via a call to RakPeerInterface::Send()\    |
| USER\_MESSAGE\_BYTES\_PUSHED,                                            |
|                                                                          |
| /// How many user message bytes were sent via a call to                  |
| RakPeerInterface::Send(). This is less than or equal to                  |
| USER\_MESSAGE\_BYTES\_PUSHED.\                                           |
| /// A message would be pushed, but not yet sent, due to congestion       |
| control\                                                                 |
| USER\_MESSAGE\_BYTES\_SENT,                                              |
|                                                                          |
| /// How many user message bytes were resent. A message is resent if it   |
| is marked as reliable, and either the message didn't arrive or the       |
| message ack didn't arrive.\                                              |
| USER\_MESSAGE\_BYTES\_RESENT,                                            |
|                                                                          |
| /// How many user message bytes were received, and returned to the user  |
| successfully.\                                                           |
| USER\_MESSAGE\_BYTES\_RECEIVED\_PROCESSED,                               |
|                                                                          |
| /// How many user message bytes were received, but ignored due to data   |
| format errors. This will usually be 0.\                                  |
| USER\_MESSAGE\_BYTES\_RECEIVED\_IGNORED,                                 |
|                                                                          |
| /// How many actual bytes were sent, including per-message and           |
| per-datagram overhead, and reliable message acks\                        |
| ACTUAL\_BYTES\_SENT,                                                     |
|                                                                          |
| /// How many actual bytes were received, including overead and acks.\    |
| ACTUAL\_BYTES\_RECEIVED,                                                 |
|                                                                          |
| If you want to track statistics over time, we also provide               |
| *Source/StatisticsHistoryPlugin.h,* used by the sample                   |
| *StatisticsHistoryTest*. It tracks values for some user-defined amount   |
| of time and does various calculations on the data set.                   |
| RakPeerInterface::GetStatistics() is read automatically. Here is sample  |
| code that tracks a sin and cos wave.                                     |
|                                                                          |
| DataStructures::Queue&lt;StatisticsHistory::TimeAndValue&gt; histogram;\ |
| StatisticsHistory::TimeAndValueQueue \*tav;\                             |
| StatisticsHistory::TimeAndValueQueue tavInst;\                           |
| StatisticsHistory statisticsHistory;\                                    |
| statisticsHistory.SetDefaultTimeToTrack(10000);\                         |
| statisticsHistory.AddObject(StatisticsHistory::TrackedObjectData(HO\_SIN |
| \_WAVE,0,0));\                                                           |
| statisticsHistory.AddObject(StatisticsHistory::TrackedObjectData(HO\_COS |
| \_WAVE,0,0));\                                                           |
| while (1) {\                                                             |
| double f = (double) ((double)GetTime() / (double)1000);\                 |
| statisticsHistory.AddValueByObjectID(HO\_SIN\_WAVE,"Waveform",sin(f),Get |
| Time(),                                                                  |
| false);\                                                                 |
| statisticsHistory.AddValueByObjectID(HO\_COS\_WAVE,"Waveform",cos(f),Get |
| Time(),                                                                  |
| false);\                                                                 |
| RakSleep(30);\                                                           |
| }\                                                                       |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

  ----------------------
  [Index](index.html)\
  ----------------------


