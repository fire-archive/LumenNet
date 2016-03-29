---
title: "Two Way Authentication Plugin Overview"
excerpt: ""
---
[block:api-header]
{
  "type": "basic",
  "title": "Securely verify a password known in advance by a pair of systems"
}
[/block]
Normally with RakNet you can transmit data securely using [secure connections](secureconnections.html). However, sometimes a pair of systems may not have secure connections active. For example, on mobiles the security code may take too much memory, be too slow, or not compile. In this case you can still verify a remote system using a password known to two systems in advance. RakNet implements this using [two way authentication](http://en.wikipedia.org/wiki/Mutual_authentication). Instead of sending the password itself, a [one way hash](http://en.wikipedia.org/wiki/Cryptographic_hash_function) of the password is sent. The hash is verified as correct or not, and the results returned to the user.
[block:api-header]
{
  "type": "basic",
  "title": "Usage:"
}
[/block]

[block:code]
{
  "codes": [
    {
      "code": "// Attach the plugin to an instance of RakPeerInterface  \nrakPeer->AttachPlugin(&twoWayAuthenticationPlugin);  \n// Add a password. The actual password (Password0) is associated with a identifier (PWD0) for faster hash lookup.  \ntwoWayAuthenticationPlugin.AddPassword(\"PWD0\", \"Password0\");  \n// Challenge another system we are connected to.  \ntwoWayAuthenticationPlugin.Challenge(\"PWD0\", remoteSystemAddressOrGuid);",
      "language": "cplusplus"
    }
  ]
}
[/block]
If the other system is also running the two way authentication plugin, and had also set the same password, you will get <span class="RakNetCode">ID_TWO_WAY_AUTHENTICATION_INCOMING_CHALLENGE_SUCCESS</span> and the other system will get <span class="RakNetCode">ID_TWO_WAY_AUTHENTICATION_OUTGOING_CHALLENGE_SUCCESS</span>. If the other system is running the plugin but has a different password, they will get <span class="RakNetCode">ID_TWO_WAY_AUTHENTICATION_INCOMING_CHALLENGE_FAILURE</span> and you will get <span class="RakNetCode">ID_TWO_WAY_AUTHENTICATION_OUTGOING_CHALLENGE_FAILURE</span>. If the other system is not running the plugin you will get <span class="RakNetCode">ID_TWO_WAY_AUTHENTICATION_OUTGOING_CHALLENGE_TIMEOUT</span>.

In the case of

*   ID_TWO_WAY_AUTHENTICATION_INCOMING_CHALLENGE_SUCCESS
*   ID_TWO_WAY_AUTHENTICATION_OUTGOING_CHALLENGE_SUCCESS
*   ID_TWO_WAY_AUTHENTICATION_OUTGOING_CHALLENGE_TIMEOUT
*   ID_TWO_WAY_AUTHENTICATION_OUTGOING_CHALLENGE_FAILURE

you can read which password challenge the message was associated with using the following code:
[block:code]
{
  "codes": [
    {
      "code": "RakNet::BitStream bs(packet->data, packet->length, false);  \nbs.IgnoreBytes(sizeof(RakNet::MessageID));  \nRakNet::RakString password;  \nbs.Read(password);",
      "language": "cplusplus"
    }
  ]
}
[/block]
All this system does is verify a password between two parties. It does not enable or disable any RakNet features, or prevent any other message from being sent during the challenge phase. However, you can pair this plugin with the [MessageFilter](messagefilter.html) plugin so that a new connection cannot send any other messages until validated. To do so, attach the [MessageFilter](messagefilter.html) plugin to RakPeerInterface before this one (actually it should be first). Call MessageFilter::SetAutoAddNewConnectionsToFilter() so that new connections are filtered. Make sure that the two way authentication messages are allowed on that same filter channel by calling MessageFilter::SetAllowMessageID(). When a connection has been validated, change the channel for that system using MessageFilter::SetSystemFilterSet().

See _Samples/TwoWayAuthentication_ for a complete sample. See TwoWayAuthentication.h for a complete list of all documented functions and parameters.

[Index](index.html) [Message Filter plugin](messagefilter.html)