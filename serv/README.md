# UDP peer to peer commincation 


<h1>./coms [my port number] [remote machine name] [remote port number]<h1>

<h1>sample run procedure running on localhost<h1>

#Steps

open the folder named serv in two terminals and run make clean before running make, note the client folder was used for testing only 

<li>first terminal: ex ./coms 6000 localhost 7000 or ./coms 6000 127.0.0.1 7000</li>
<li>second terminal:ex ./coms 7000 localhost 6000 or ./coms 7000 127.0.0.1 6000</li>

<li>terminate on both machines or terminals by typing ! on any machine or terminal</li>

send and receive messges between the two terminal. Same procedure applies to remote machines

