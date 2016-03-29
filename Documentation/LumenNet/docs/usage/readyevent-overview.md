---
title: "ReadyEvent Overview"
excerpt: ""
---
[block:api-header]
{
  "type": "basic",
  "title": "Signal that an event is ready to proceed"
}
[/block]
ReadyEventlets you toggle ready or unready on a numbered event for a peer to peer system. It handles the networking telling you which system(s) are ready, and if all systems are ready. The non-trivial problem that it solves is to validate that all systems know that all other systems are ready, not just that all systems you know about are ready. To clarify, if A is connected to B and C, and B and C broadcast that they are ready, A knows that B and C are ready. However, A would not normally know that the packet from B to C has arrived, which it may not have due to latency or packetloss. The problem with this is that A may start sending some kind of start gameplay packets to B and C, yet B and C each thought the other was not ready yet.

ReadyEvent solves this in two stages. In the first stage, it waits for all systems we know about to be ready. In the second stage, a message is sent querying if all systems we are connected to are also in that state. ReadyEvent::IsEventCompletionProcessing() will return true during the second stage. After the second stage, ID_READY_EVENT_ALL_SET is returned to the user.
[block:api-header]
{
  "type": "basic",
  "title": "Example usage:"
}
[/block]
1.  Add all systems participating or joining the session using AddToWaitList()
2.  Optionally broadcast information corresponding to the event. Then call SetReady() to toggle ready or unready as long as IsEventCompletionProcessing() return false.
3.  When ID_READY_EVENT_ALL_SET is returned, or IsEventCompleted() returns true, and you want to consider this event done, call ForceCompletion() on one or more of the systems. This will make it so remote systems can no longer call SetReady(false)
4.  Proceed with gameplay that assumes the event with the specified eventId is ready.
5.  When you no longer need a partcular eventId, or want to reuse that ID (such as with an enumeration), use DeleteEvent() to free the memory.

ReadyEvent is primarily useful when game has stages, and a stage cannot proceed until peer to peer communication has occured between all systems. For example, suppose you have a peer to peer turn based game where every system needs one action from every other system before going to the next turn. Without ReadyEvent, the session host may signal &quot;next turn&quot; yet one of the remote systems did not yet get all actions from all other systems.