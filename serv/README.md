# UDP peer to peer commincation 


./coms [my port number] [remote machine name] [remote port number]

#sample run procedure running on localhost

#Steps

open the folder named serv in two terminals and run make clean before running make, note the client folder was used for testing only 

first terminal: ex ./coms 6000 localhost 7000 or ./coms 6000 127.0.0.1 7000
second terminal:ex ./coms 7000 localhost 6000 or ./coms 7000 127.0.0.1 6000

terminate on both machines or terminals by typing ! on any machine or terminal

send and receive messges between the two terminal. Same procedure applies to remote machines


