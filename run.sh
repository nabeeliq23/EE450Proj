# Open the first terminal and run script 1
gnome-terminal --title "Main Server" -- bash -c "./serverM; exec bash"

# Open the second terminal and run script 2
gnome-terminal --title "CE Server" -- bash -c "./serverCE; exec bash"

# Open the third terminal and run script 3
gnome-terminal --title "EE Server" -- bash -c "./serverEE; exec bash"

# Open the fourth terminal and run script 4
gnome-terminal --title "Client" -- bash -c "./client; exec bash"
