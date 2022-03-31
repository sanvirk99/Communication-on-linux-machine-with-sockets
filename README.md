 # UDP peer to peer commincation 


<li>./coms [my port number] [remote machine name] [remote port number]</li>

<h1>Sample run procedure running on localhost</h1>

<b>Steps</b>

<li>open serv folder,run make clean then make, note folder named client only used for testing</li> 
<li>open the folder named serv in two terminals</li>

<li>first terminal: ex <b>./coms 6000 localhost 7000</b> or <b>./coms 6000 127.0.0.1 7000</b></li>
<li>second terminal:ex <b>./coms 7000 localhost 6000</b> or <b>./coms 7000 127.0.0.1 6000</b></li>

<li>terminate on both machines or terminals by typing ! on any machine or terminal</li>

<br></br>

<b>Send and receive messges between the two terminal. Same procedure applies to remote machines</b>
