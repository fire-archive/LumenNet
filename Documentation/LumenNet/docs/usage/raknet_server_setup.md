---
title: "RakNet Server Setup"
excerpt: ""
---
[block:api-header]
{
  "type": "basic",
  "title": "Setting up Master Server 2 / Lobby 3 / NAT Punchthrough on a Windows"
}
[/block]

[block:api-header]
{
  "type": "basic",
  "title": "Step 1: Rent a dedicated server"
}
[/block]
Specifications:

* Either 8 or 16 GB of RAM
* Speed does not matter
* Harddrive space does not matter, generally 64 GB is enough. I recommend an SSD harddrive however.
* Traffic should be 10 TB or more
* 100 Mbps Uplink Port is sufficient for ONLY Master Server 2. However, if you run Lobby3 / NAT Punchthrough on this server as well, you should use 10000 Mbps
* RAID is not necessary and will not help for Master Server 2. However, if you also use the server for Lobby3 then this will provide redundancy.
* Only one IP address is needed for Master Server 2, Lobby 3. NAT punchthrough requires a total of two IP addresses. NAT type detection requires a total of 4. The IP addresses are not exclusive, so 4 is sufficient for all services.
* No firewall, including Windows Firewall.
* OS should be Windows, any version. I am assuming 64 bit in these instructions. This system will probably work with other OS’s, however only Windows has been tested. I am assuming access is done through remote desktop.
* SQL is not needed
* I am using http://www.razorservers.com/ with 16 GB RAM at under $200 a month. After purchase, you should get an email or webpage indicating your IP address, username / login, and password
[block:api-header]
{
  "type": "basic",
  "title": "Step 2: Download and install BigMemory MAX (Used for Master Server 2 and Lobby3)"
}
[/block]
Go to http://terracotta.org/products/bigmemory and click “Free Download” under the column “BigMemory Max”
[block:image]
{
  "images": [
    {
      "image": [
        "https://www.filepicker.io/api/file/9hlsn6cSQbLAWC8qMJPg",
        "Teracotta.jpg",
        "643",
        "620",
        "#c87b3a",
        ""
      ]
    }
  ]
}
[/block]
If done correctly, you should have a directory on your harddrive similar to C:\bigmemory-max-4.0.1 . MasterServer2 has been build with 4.0.1, so you will need this specific version. You should also get an email containing a file ‘terracotta-license.key’. Save this file to "C:\bigmemory-max-4.0.1\terracotta-license.key" The server will look for it here on startup.
Edit start-tc-server.bat
Open "C:\bigmemory-max-4.0.1\server\bin\start-tc-server.bat" and find this line:
set JAVA_OPTS=%OPTS% %JAVA_OPTS%
Change it to
set JAVA_OPTS=%OPTS% %JAVA_OPTS% -Xms1024m -Xmx1024m -XX:MaxDirectMemorySize=8448m
Create and paste tc-config.xml
Go to C:\bigmemory-max-4.0.1\server\bin and create a file tc-config.xml
If your server has 8 GB of RAM, paste these contents

<!--All content copyright (c) 2003-2008 Terracotta, Inc.,
 except as may otherwise be noted in a separate copyright notice.
 All rights reserved-->
<!--This config file is used by the server and bootjar tool when none is specified.-->
<tc:tc-config xmlns:tc="http://www.terracotta.org/config">
  <servers>
    <server>
      <offheap>
        <enabled>true</enabled>
	<maxDataSize>1.5G</maxDataSize>
      </offheap>
      <data>%(user.home)/terracotta/4.0.1/server-data</data>
      <logs>%(user.home)/terracotta/4.0.1/server-logs</logs>
    </server>
    <restartable enabled="true"/>
  </servers>
  <clients>
    <logs>%(user.home)/terracotta/4.0.1/client-logs</logs>
  </clients>
</tc:tc-config>
If your server has 16 GB of RAM or higher, paste these contents
<!--All content copyright (c) 2003-2008 Terracotta, Inc.,
 except as may otherwise be noted in a separate copyright notice.
 All rights reserved-->
<!--This config file is used by the server and bootjar tool when none is specified.-->
<tc:tc-config xmlns:tc="http://www.terracotta.org/config">
  <servers>
    <server>
      <offheap>
        <enabled>true</enabled>
	<maxDataSize>8G</maxDataSize>
      </offheap>
      <data>%(user.home)/terracotta/4.0.1/server-data</data>
      <logs>%(user.home)/terracotta/4.0.1/server-logs</logs>
    </server>
    <restartable enabled="true"/>
  </servers>
  <clients>
    <logs>%(user.home)/terracotta/4.0.1/client-logs</logs>
  </clients>
</tc:tc-config>
[block:api-header]
{
  "type": "basic",
  "title": "License GeoIP City"
}
[/block]
Used for Master Server 2 and Lobby3


[block:image]
{
  "images": [
    {
      "image": [
        "https://www.filepicker.io/api/file/wxqow5wJQbel180HbOHv",
        "GeoIPCity.jpg",
        "987",
        "678",
        "#5786bb",
        ""
      ]
    }
  ]
}
[/block]
<span class="c2">Login and download the Binary Format for APIs</span>

<span>After purchase, login and download “GeoIP City” in the format “Binary Format for APIs”. You may have a newer version, so the ID GEO-133 may not match exactly.  The download should contain a binary file GeoIPCity.dat. Save this file (you will need it later)</span>

<span style="overflow: hidden; display: inline-block; margin: 0.00px 0.00px; border: 0.00px solid #000000; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px); width: 624.00px; height: 657.47px;">![D:\temp\Untitled-2.jpg](images/image01.jpg)</span>
[block:image]
{
  "images": [
    {
      "image": [
        "https://www.filepicker.io/api/file/Ltbvxc1lQMevUzzVK2bT",
        "image02.jpg",
        "987",
        "678",
        "#0e91c8",
        ""
      ]
    }
  ]
}
[/block]
* * *

<span class="c7">Step 4: Install Java</span> <span class="c7 c2">JDK 6</span><span class="c7">.  
(Used for Master Server 2 and Lobby3)</span>

*   <span class="c4">Go to</span> <span class="c4 c9 c2">[http://www.oracle.com/technetwork/java/javase/archive-139210.html](https://www.google.com/url?q=http://www.oracle.com/technetwork/java/javase/archive-139210.html&sa=D&ust=1456140971901000&usg=AFQjCNGs2tfpGBW6GzvLBIDpiZp6ziweZg)</span>
*   <span class="c4">Click Java SE 6\.</span> <span class="c7 c15">DO NOT INSTALL JAVA JDK 7</span>
*   <a id="h.gjdgxs"></a><span class="c4">Click ‘Java SE Development Kit 6u43’</span>
*   <span class="c4">Accept the license agreement</span>
*   <span class="c4">Download and install jdk-6u43-windows-x64.exe</span>

<span>If done correctly, you should have C:\Program Files\Java\jdk1.6.0_43 or a similar path on your harddrive.</span>

<span>If you do not already have it, add an environment variable JAVA_HOME with the value C:\Program Files\Java\jdk1.6.0_43 . If you do not know how to do this, search for “How to add an environment variable”. Here is an example  
</span><span class="c9 c2">[http://www.itechtalk.com/thread3595.html](https://www.google.com/url?q=http://www.itechtalk.com/thread3595.html&sa=D&ust=1456140971904000&usg=AFQjCNHohLa-h9NMis7-h0MUsJA-gfeqbA)</span>

<span>You can test this by opening a command prompt and typing echo %java_home%. It should print something like C:\Program Files\Java\jdk1.6.0_37</span>

* * *

<span></span>

<span class="c7">Step 5: Download Apache Tomcat  
(Used for Master Server 2 and Lobby3)</span>

<span>Go to</span> <span class="c9 c2">[http://tomcat.apache.org/](https://www.google.com/url?q=http://tomcat.apache.org/&sa=D&ust=1456140971906000&usg=AFQjCNE3S083lWQkhWt2KudAEKrbE7cjlg)</span><span> and install the latest version of Tomcat, under Binary Distributions / Core / 64-bit Windows zip. Use the tar.gz version.</span>

<span style="overflow: hidden; display: inline-block; margin: 0.00px 0.00px; border: 0.00px solid #000000; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px); width: 622.87px; height: 634.07px;">![D:\temp\Untitled-3.jpg](images/image04.jpg)</span>
[block:image]
{
  "images": [
    {
      "image": [
        "https://www.filepicker.io/api/file/BgHJ88EvT2C5siGo6gaY",
        "image03.jpg",
        "394",
        "436",
        "#3d5b79",
        ""
      ]
    }
  ]
}
[/block]

[block:image]
{
  "images": [
    {
      "image": [
        "https://www.filepicker.io/api/file/4kNPovouQlebjVc1Ipw1",
        "image04.jpg",
        "836",
        "851",
        "#944f4b",
        ""
      ]
    }
  ]
}
[/block]
<span>Unzip to your harddrive. You should have something similar to C:\apache-tomcat-7.0.37</span>

* * *

<span></span>

<span class="c7">Step 6: Setup Apache Tomcat  
(Used for Master Server 2 and Lobby3)</span>

<span>Apache Tomcat setup is confusing, so follow these instructions carefully. Also, note that Apache Tomcat and Apache are different things and nowhere is this really explained, which confused me for many days. If you run into problems, be careful to search for “Tomcat” and not Apache.</span>

<span class="c2">Add an environment variable CATALINA_HOME</span>

<span>Set CATALINA_HOME to where you unzipped Apache Tomcat, for example C:\apache-tomcat-7.0.39 . This is important or else your webpage will not show up later for what seems to be inexplicable reasons.</span>

<span style="overflow: hidden; display: inline-block; margin: 0.00px 0.00px; border: 0.00px solid #000000; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px); width: 525.80px; height: 581.60px;">![D:\temp\Untitled-4 copy.jpg](images/image03.jpg)</span>
[block:image]
{
  "images": [
    {
      "image": [
        "https://www.filepicker.io/api/file/0JCltyZGSMeLAvsV9gWZ",
        "image03.jpg",
        "394",
        "436",
        "#3d5b79",
        ""
      ]
    }
  ]
}
[/block]
<span>(Apache Tomcat sometimes refers to itself as Catalina)</span>

<span></span>

<span class="c2">Open the file "C:\apache-tomcat-7.0.39\conf\server.xml" in a text editor</span>

<span>This file contains most (but not all) of the setting related to your webpage deployment.  Find the block that looks like this:</span>

<span class="c11"><Host name="localhost"  appBase="webapps"</span>

<span class="c11">            unpackWARs="true" autoDeploy="true"></span>

<span>The <Host …> block tells Apache Tomcat where to find your webpage(s) on the harddrive.</span>

<span class="c2">Set your <Host> block to your domain</span>

<span class="c11"><Host name="www.masterserver2.raknet.com" appBase="RakNet/masterserver2" unpackWARs="true" autoDeploy="true"></span>

<span>If you want more than one domain for the same website, you can use <Alias> such as</span>

<span class="c11"><Host name="www.masterserver2.raknet.com" appBase="RakNet/masterserver2" unpackWARs="true" autoDeploy="true"></span>

<span class="c11"><Alias>masterserver2.raknet.com</Alias></span>

<span class="c11"><Alias>mygame.masterserver2.raknet.com</Alias></span>

<span class="c11"></Host></span>

<span>If you want to set an error page for direct  IP address, also add this line:</span>

<span class="c11"><Host name="localhost" appBase="webapps/error" unpackWARs="true" autoDeploy="true"> </Host></span>

<span>Then have a file "C:\apache-tomcat-7.0.39\webapps\error\ROOT\index.html" where index.html contains an error message.</span>

<span>Otherwise, you can point it to either Lobby 3 or Master Server 2</span>

<span class="c11"><Host appBase=="RakNet/masterserver2" autoDeploy="true" name="localhost" unpackWARs="true"></span>

<span class="c2">Change your webpage port from 8080 to 80</span>

<span class="c11"><Connector port="8080" protocol="HTTP/1.1"</span>

<span class="c11">               connectionTimeout="20000"</span>

<span class="c11">               redirectPort="8443" /></span>

<span>To</span>

<span class="c11"><Connector port="80" protocol="HTTP/1.1"</span>

<span class="c11">               connectionTimeout="20000"</span>

<span class="c11">               redirectPort="443" /></span>

<span>Port 80 is the default port webbrowsers use to find your webpage. If you leave it at 8080, then you would have to access the url with :8080 at the end, such as www.masterserver2.raknet.com:8080</span>

<span class="c2">Increase the memory given to Apache Tomcat</span>

<span>Next, you will need to increase the amount of memory given to Apache Tomcat, in this case 2.5 GB. How to set Apache Tomcat environment variables is difficult to figure out, due to conflicting and wrong information on the web about how to do it.</span>

<span>The correct way on Windows:</span>

<span>Go to C:\apache-tomcat-7.0.39\bin or equivalent, and add a file setenv.bat . Paste this into the contents of the file:</span>

<span class="c11">set CATALINA_OPTS=-Xms2560m -Xmx2560m -Dcom.tc.tc.config.total.timeout=5000</span>

<span class="c2">Place and unzip ROOT.war so Apache Tomcat can find it</span>

<span>You will be provided a ROOT.war for Master Server 2, and another for Lobby3\. For Lobby3, place it at "C:\apache-tomcat-7.0.39\RakNet\lobby3\ROOT.war". Delete any other files at that location. For Master Server 2, place it at "C:\apache-tomcat-7.0.39\RakNet\masterserver2\ROOT.war". Delete any other files at that location.</span>

<span>Next, unzip ROOT.war using 7-zip (</span> <span class="c9 c2">[http://www.7-zip.org/](https://www.google.com/url?q=http://www.7-zip.org/&sa=D&ust=1456140971916000&usg=AFQjCNF6qSJZC8jsbztarxH9Eq4mN3_42Q)</span><span> ), or an alternative</span>

<span>If done correctly, you will have a file "C:\apache-tomcat-7.0.39\RakNet\lobby3\ROOT.war" In that same directory, you will have a directory "C:\apache-tomcat-7.0.39\RakNet\lobby3\ROOT". In "C:\apache-tomcat-7.0.39\RakNet\lobby3\ROOT" you should have index.html and numerous other files.</span>

<span class="c2">Copy BigMemory license file</span>

<span>Find "C:\bigmemory-max-4.0.1\terracotta-license.key"</span>

<span>MasterServer2: Copy it to C:\apache-tomcat-7.0.39\RakNet\masterserver2\ROOT\WEB-INF\classes  
Lobby3: Copy it to C:\apache-tomcat-7.0.39\RakNet\lobby3\ROOT\WEB-INF\classes</span>

<span class="c2">Copy GeoIP database file</span>

<span>Find ‘GeoIPCity.dat’ you saved in step 3\. The location to place it is the same as the BigMemory license files</span>

<span>MasterServer2: Copy it to C:\apache-tomcat-7.0.39\RakNet\masterserver2\ROOT\WEB-INF\classes  
Lobby3: Copy it to C:\apache-tomcat-7.0.39\RakNet\lobby3\ROOT\WEB-INF\classes</span>

<span class="c11"></span>

* * *

<span class="c11"></span>

<span class="c7">Step 7: Setup SSL  
(Used for Lobby3 only)</span>

<span>SSL is not necessary for MasterServer 2\. It is necessary for Lobby3, and if you use Lobby3 on the same server you will need to follow these steps at some point.</span>

<span>To use SSL, you can use a self-signed key or you can purchase a key from a certificate authority. A self-signed key can be used for testing, before you spend money buying an SSL certificate.</span>

<span class="c2">Get the Tomcat Native Connector</span>

<span>Go to</span> <span class="c9 c2">[http://apache.mirrors.lucidnetworks.net/tomcat/tomcat-connectors/native/1.1.27/binaries/](https://www.google.com/url?q=http://apache.mirrors.lucidnetworks.net/tomcat/tomcat-connectors/native/1.1.27/binaries/&sa=D&ust=1456140971920000&usg=AFQjCNElXn106SuPM1sGSQwMFrULylUb0w)</span><span> and download tomcat-native-1.1.27-win32-bin.zip . This is the ‘Tomcat Native Connector’ which is faster for SSL and enables APR, or something like that. All I know it the system inexplicably won’t work without it.</span>

<span>In the zip, find bin/x64/tcnative-1.dll. tcnative-1.dll is in the zip file three times, so use this exact one. I’m not sure what the other two are for, or what the difference is, except they do not work. Copy tcnative-1.dll to C:\apache-tomcat-7.0.37\bin or your equivalent.</span>

<span class="c2">(Option 1) Get a self-signed key</span>

<span>Go here  
</span><span class="c9 c2">[http://www.selfsignedcertificate.com/](https://www.google.com/url?q=http://www.selfsignedcertificate.com/&sa=D&ust=1456140971921000&usg=AFQjCNHOL3EQ5TWmqXU930VOUEv20OINAg)</span>

<span>Enter your web address, press generate, download the .key and .cert files, and put them in a new directory C:\apache-tomcat-7.0.39\conf\raknet (you can rename raknet to something else if desired).</span>

<span class="c2">(Option 2) Get an SSL certificate from a certificate authority</span>

<span>I ordered an SSL certificate from</span> <span class="c9 c16">[http://www.rapidssl.com/](https://www.google.com/url?q=http://www.rapidssl.com/&sa=D&ust=1456140971922000&usg=AFQjCNHlpc0t1P85jRYDcAXHjzF2C9l9Lg)</span><span> although there are many ssl certificate vendors to order from. There are a lot of unnecessary options they try to sell you, just ignore that and do whatever is cheapest, except possibly for the validity period. You should set that for as many years as you need the certificate.</span>

<span>After you order the certificate, you will get an email asking you to confirm it.</span>

<span>Once the certificate is confirmed, you will need the public, intermediate, and private keys. I had to specifically ask for this by email, once the certificate was confirmed. I was given 3 files, intermediate.txt, lobby3.raknet.com.txt, privatekey.txt</span>

<span class="c2">Setup SSL connectors:</span>

<span>Open "C:\apache-tomcat-7.0.37\conf\server.xml" again, and find this block of code you edited earlier:</span>

<span class="c11"><Connector port="80" protocol="HTTP/1.1"</span>

<span class="c11">               connectionTimeout="20000"</span>

<span class="c11">      &nbsnbsp;        redirectPort="443" /></span>

<span>Immediately after that block, add something similar to this:</span>

<span class="c11"><Connector port="443" protocol="org.apache.coyote.http11.Http11AprProtocol" SSLEnabled="true"</span>

<span class="c11">               maxThreads="150" scheme="https" secure="true"</span>

<span class="c11">               clientAuth="false" sslProtocol="SSLv3"</span>

<span class="c11">               SSLCertificateKeyFile="${catalina.base}\conf\lobby3\privatekey.txt"</span>

<span class="c11">               SSLCertificateFile="${catalina.base}\conf\raknet\lobby3.raknet.com.txt"</span>

<span class="c11">                /></span>

<span>In the text above, replace paths for SSLCertificateKeyFile and SSLCertificateFile accordingly. SSLCertificateKeyFile is for the private key (may be named privatekey.txt for example) and SSLCertificateFile is for your website certificate, such as masterserver2.raknet.com.txt. You do not need the intermediate key, if you were given one.</span>

<span>You can have multiple connectors if you want more than one website hosted by this server. However, each connector will need a different port.</span>

<span>Note that Skype also uses port 443\. Either turn off Skype on this computer, or change it to not use 443.  
</span><span class="c9 c2">[http://sharovatov.wordpress.com/2009/06/08/skype-blocking-80-and-443-ports/](https://www.google.com/url?q=http://sharovatov.wordpress.com/2009/06/08/skype-blocking-80-and-443-ports/&sa=D&ust=1456140971927000&usg=AFQjCNE8do2JwIhL_pO1bPRmR4gitlwEcA)</span>

* * *

<span class="c7">Step 8: Download and setup hMail Server  
(Used for Lobby3 only)</span>

<span class="c2">Download and install hMail Server</span><span style="overflow: hidden; display: inline-block; margin: 0.00px 0.00px; border: 0.00px solid #000000; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px); width: 622.87px; height: 406.33px;">![D:\temp\Untitled-3.jpg](images/image06.jpg)</span>
[block:image]
{
  "images": [
    {
      "image": [
        "https://www.filepicker.io/api/file/1rm5WuzdS2CYP3spZSPW",
        "image06.jpg",
        "799",
        "521",
        "#b53c28",
        ""
      ]
    }
  ]
}
[/block]
<span class="c7"></span>

<span class="c2">Setup your domain for hMail Server</span>

1.  <span class="c4">Open the hMailServer Administrator program.</span>
2.  <span class="c4">Click Add Domain. Add your domain (such as lobby3.mygame.com)</span>
3.  <span class="c4">Expand the accounts tab, and create an account ‘lobby3’  
    Set the account password to a desired value. This same value should be saved in C:\apache-tomcat-7.0.39\RakNet\lobby3\ROOT\WEB-INF\classes\settings.xml in the emailAccountPassword section. Also set the username under emailAccountUsername and the full email address under mail.smtp.user</span>
4.  <span class="c4">Under settings / advanced / ip ranges / internet, uncheck allow connections for everything</span>
5.  <span class="c4">Do NOT set bind to local ip address under advanced, or remote host name under SMTP relayer</span>

<span style="overflow: hidden; display: inline-block; margin: 0.00px 0.00px; border: 0.00px solid #000000; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px); width: 622.87px; height: 418.60px;">![D:\temp\Untitled-4.jpg](images/image05.jpg)</span>
[block:image]
{
  "images": [
    {
      "image": [
        "https://www.filepicker.io/api/file/1UyTCcySnqqMHaeL5ZPd",
        "image05.jpg",
        "894",
        "600",
        "#b45244",
        ""
      ]
    }
  ]
}
[/block]
* * *

<span class="c9 c2"></span>

<span class="c7">Step 9: Start BigMemory  
(Used for Master Server 2 and Lobby3)</span>

<span>Create a shortcut to "C:\bigmemory-max-4.0.1\server\bin\start-tc-server.bat" and place it on the desktop.</span>

<span class="c2">To startup BigMemory:</span>

<span>Double the shortcut, and BigMemory should start. If you run that batch from from the command prompt, you will need the –f option to tell it where to find tc-config.xml. For example: start-tc-server.bat -f "C:\bigmemory-max-4.0.1\server\bin\tc-config.xml"</span>

<span>Wait a while, and you should get a console window that shows text similar to this:</span>

<span>2013-07-28 10:15:52,522 INFO - Available Max Runtime Memory: 981MB  
2013-07-28 10:15:52,711 INFO - JMX Server started. Available at URL[service:jmx:jmxmp://0.0.0.0:9520]  
2013-07-28 10:15:59,986 INFO - Becoming State[ ACTIVE-COORDINATOR ]  
2013-07-28 10:16:00,003 INFO - Terracotta Server instance has started up as ACTIVE node on 0.0.0.0:9510 successfully, and is now ready for work.  
Jul 28, 2013 10:16:00 AM com.sun.jersey.server.impl.application.WebApplicationImpl _initiate INFO: Initiating Jersey application, version 'Jersey: 1.16 11/28/2012 02:09 PM'  
Jul 28, 2013 10:16:00 AM com.sun.jersey.server.impl.application.DeferredResource Config$ApplicationHolder <init>  
INFO: Instantiated the Application class com.terracotta.management.ApplicationTs</span>

<span class="c2">To shutdown BigMemory:</span>

<span>Run "C:\bigmemory-max-4.0.1\server\bin\stop-tc-server.bat"</span>

<span>DO NOT JUST CLOSE THE CONSOLE WINDOW. YOU MAY LOSE DATA.</span>

<span class="c2">BigMemory has a management console</span>

<span>Create a shortcut to “C:\bigmemory-max-4.0.1\tools\management-console\bin\start-tmc.bat" and place it on the desktop. Double click it. You should get text similar to this:</span>

<span>Starting Terracotta Management Console at http://localhost:9889/tmc</span>

<span>2013-07-28 10:23:06.184:INFO::Redirecting stderr/stdout to D:\bigmemory-max-4.0.1\tools\management-console\logs\2013_07_28.stderrout.log</span>

<span>Open a web browser, and in the URL field paste</span> <span class="c9 c2">[http://localhost:9889/tmc/](https://www.google.com/url?q=http://localhost:9889/tmc/&sa=D&ust=1456140971933000&usg=AFQjCNGfHwbhuvE5iLDbVf5k3bQwQWoTVQ)</span><span>  
Ensure that the webpage loads. You will probably see “There are no CacheManagers” which is fine.</span>

<span>To shutdown the management console, use "C:\bigmemory-max-4.0.1\tools\management-console\bin\stop-tmc.bat"</span>

<span class="c2">Data backups (Lobby3 only):</span>

<span>To make backups of your data (Lobby3 only) you can do so via the management console under Administration / Backups</span>

<span>Backups are stored to C:\bigmemory-max-4.0.1\server\bin\data-backup with the directory name as the date.</span>

<span>To restore from a backup, so something similar to this:</span>

<span>del C:\Users\Administrator\terracotta\4.0.1\server-data\index  
copy C:\bigmemory-max-4.0.1\server\bin\data-backup\backup.20130624.170502\index C:\Users\Administrator\terracotta\4.0.1\server-data\index  
del C:\Users\Administrator\terracotta\4.0.1\server-data\objectdb  
copy C:\bigmemory-max-4.0.1\server\bin\data-backup\backup.20130624.170502\data\objectdb C:\Users\Administrator\terracotta\4.0.1\server-data\objectdb</span>

<span>I am not sure how to make automatic backups at this time, although I know it is possible.</span>

<span>This same process can be used to load a backup onto another computer, in case you need to migrate your data.</span>

* * *

<span></span>

<span class="c7">Step 10: Start Apache Tomcat  
(Used for Master Server 2 and Lobby3)</span>

<span class="c2">To startup Apache Tomcat</span>

<span>Create a shortcut to "C:\apache-tomcat-7.0.39\bin\startup.bat" and paste it on your desktop. Be sure BigMemory is already running. Double click your new shortcut. A lot of text will scroll off the screen. This text should show on startup:</span>

<span style="overflow: hidden; display: inline-block; margin: 0.00px 0.00px; border: 0.00px solid #000000; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px); width: 624.00px; height: 359.47px;">![D:\temp\copy.jpg](images/image08.jpg)</span><span>  
</span><span class="c7">Starting up</span>
[block:image]
{
  "images": [
    {
      "image": [
        "https://www.filepicker.io/api/file/hm6bCW5yRCeLVOBD2LFI",
        "image08.jpg",
        "677",
        "390",
        "#934a46",
        ""
      ]
    }
  ]
}
[/block]
<span class="c7"></span>

<span style="overflow: hidden; display: inline-block; margin: 0.00px 0.00px; border: 0.00px solid #000000; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px); width: 624.00px; height: 359.47px;">![](images/image07.png)</span><span class="c7">Loaded successfully</span>
[block:image]
{
  "images": [
    {
      "image": [
        "https://www.filepicker.io/api/file/tf9mIH9mTfKNpM1inUyK",
        "image07.png",
        "677",
        "390",
        "#769498",
        ""
      ]
    }
  ]
}
[/block]
<span>Errors are easy to miss, so be careful the first time you run that nothing shows up looking like an error</span>

<span class="c2">Test localhost</span>

<span>You should be able to go to</span> <span class="c9 c2">[http://localhost/](https://www.google.com/url?q=http://localhost/&sa=D&ust=1456140971938000&usg=AFQjCNFE5dUc3G1MWS7PQYzgoM4Qu7RwFg)</span><span> in your webbrowser and see whatever page you set it to in your <Host> section in server.xml for Apache Tomcat.</span>

<span class="c2">Shutting down Apache Tomcat</span>

<span>Use "C:\apache-tomcat-7.0.37\bin\shutdown.bat" do not just close the window.  
Always shutdown Tomcat this way, and wait for the console window to close, before shutting down BigMemory, to avoid data loss.</span>

<span class="c2">Setup DNS</span>

<span>Search for DNS hosting if you do not know how to do this. If you have a webpage already, you might be able to set it up in the control panel</span>

<span style="overflow: hidden; display: inline-block; margin: 0.00px 0.00px; border: 0.00px solid #000000; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px); width: 624.00px; height: 277.93px;">![D:\temp\Untitled-6.jpg](images/image09.jpg)</span>
[block:image]
{
  "images": [
    {
      "image": [
        "https://www.filepicker.io/api/file/moSDgXuSSMa4zN6HVBHS",
        "image09.jpg",
        "541",
        "241",
        "#416c9d",
        ""
      ]
    }
  ]
}
[/block]
<span>Set the DNS entry to the static IP address of your server</span>

<span class="c2">Test remote</span>

<span>If you set a host name other than localhost (that is, you set HOST name=www.masterserver2.raknet.com), you should be able to visit that URL in a webbrowser once you have setup the corresponding DNS entry.</span>

* * *

<span></span>

<span class="c7">Step 11: Run NAT Punchthrough / NAT Type detection</span>

<span class="c2">Download RakNet  
</span><span class="c9 c2">[http://www.raknet.com/download.html](https://www.google.com/url?q=http://www.raknet.com/download.html&sa=D&ust=1456140971941000&usg=AFQjCNEBRZxfyEKyeyICPlaE2hCkN6AV4A)</span>

<span class="c2">Install Visual Studio Express if you do not have it already  
</span><span class="c9 c2">[http://www.microsoft.com/visualstudio/eng/downloads#d-express-windows-desktop](https://www.google.com/url?q=http://www.microsoft.com/visualstudio/eng/downloads%23d-express-windows-desktop&sa=D&ust=1456140971942000&usg=AFQjCNG5RIAOLK3cqy3Yd_qr0ujmCixe2g)</span>

<span class="c2">Build</span>

<span>Open RakNet_VS2008.sln, convert, build the project NATCompleteServer. Right click NATCompleteServer and Set as Startup Project if it was not already.</span>

<span class="c2">Run</span>

<span>Go to Debug / Start Debugging to run NATCompleteServer.  If you want a port other than the default, pass this on the command line.</span>

<span></span>

<span> </span>