import socket
import tkinter as tk

global speed
global last_button_state
last_button_state = "not_pressed"
key_pressed = False

def set_key_pressed(value):
    global key_pressed
    key_pressed = value
    not_pressed()

# Define a function to update the IP address based on the value in the text field
def update_ip_address():
    global ip_address
    ip_address = ip_address_entry.get()
    print("IP address updated to:", ip_address)

def send_message(message): 
    # Send a message to the destination device
    udp_socket.sendto(message.encode(), (ip_address, port))
    print("Message", message, "sent")
    
# Define the function to be called when the button is clicked
def move_forward():
    send_message('A')

def move_left():
    send_message("R")

def move_right():
    send_message("L")

def move_backward():
    send_message('B')

# Define the function to be called when the slider is moved
def set_speed(value):
    speed = value
    print("Speed:", speed)
    
    # Update the speed in the Arduino
    send_message(speed)

def not_pressed():
    global last_button_state
    global key_pressed

    # Check if a key is being pressed
    if key_pressed:
        last_button_state = "pressed"
    else:
        if last_button_state == "not_pressed":
            return  # Avoid spamming the console with the same message
        else:
            last_button_state = "not_pressed"
            print("No button pressed")
            send_message("E")

    # Schedule the next call to this function
    window.after(100, not_pressed)

# Define the IP address and port of the destination device
ip_address = '192.168.1.127' 
port = 2390

# Create a UDP socket
udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Create a new window
window = tk.Tk()

# Add a label to the window
label = tk.Label(text="Zinnobot & Vitbot \n Remote Controller v1.0")
label.pack()

# Add a text field to the window for entering the IP address
ip_address_entry = tk.Entry(window, width=20)
ip_address_entry.insert(0, ip_address)
# Add a button to the window for updating the IP address
ip_address_button = tk.Button(window, text="Update IP Address", command=update_ip_address)
ip_address_button.pack()
ip_address_entry.pack()

# Add a slider to the window
speed_slider = tk.Scale(window, from_=100, to=250, orient=tk.HORIZONTAL, command=set_speed, resolution=15)
speed_slider.pack()

# Add buttons to the window
button_forward = tk.Button(window, text="Forward", command=move_forward, width=10, height=3)
button_forward.pack(side=tk.TOP)

button_left = tk.Button(window, text="Left", command=move_left, width=10, height=3)
button_left.pack(side=tk.LEFT)

button_right = tk.Button(window, text="Right", command=move_right, width=10, height=3)
button_right.pack(side=tk.RIGHT)

button_backward = tk.Button(window, text="Backward", command=move_backward, width=10, height=3)
button_backward.pack(side=tk.BOTTOM)

# Bind keyboard keys to button functions
window.bind("<Up>", lambda event: (button_forward.invoke(), set_key_pressed(True)))
window.bind("<Left>", lambda event: (button_left.invoke(), set_key_pressed(True)))
window.bind("<Right>", lambda event: (button_right.invoke(), set_key_pressed(True)))
window.bind("<Down>", lambda event: (button_backward.invoke(), set_key_pressed(True)))
window.bind("<KeyRelease>", lambda event: set_key_pressed(False))

# Set the key_pressed flag to False when the window loses focus
window.bind("<FocusOut>", lambda event: set_key_pressed(False))

# Schedule the first call to the not_pressed function
window.after(100, not_pressed)

# Run the main loop
window.mainloop()

# Close the socket
udp_socket.close()