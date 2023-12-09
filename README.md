# face-detection-auto-door-lock
import cv2
from ultralytics import YOLO
import serial

# Load the YOLOv8 model
model = YOLO('best.pt')

# Open the video file
video_path = "path/to/your/video/file.mp4"
cap = cv2.VideoCapture(0)
serial_port = "COM3"  # Change this to your specific port (e.g., "/dev/ttyUSB0" on Linux)
baud_rate = 9600

# Create a serial object
ser = serial.Serial(serial_port, baud_rate, timeout=1)

# Loop through the video frames
while cap.isOpened():
    # Read a frame from the video
    success, frame = cap.read()

    if success:
        # Run YOLOv8 inference on the frame
        results = model(frame, conf=0.5)

        # Check if there are any detections
        if results[0]:
            # Execute your code when an object is detected
            print("Object detected")

            # Send command to Arduino to move the servo
            data_to_send = "1"  # You may need to adjust this value based on your Arduino code
            ser.write(data_to_send.encode())  # Convert string to bytes before sending
        else:
            # Send command to Arduino indicating no detection
            data_to_send = "0"  # You may need to adjust this value based on your Arduino code
            ser.write(data_to_send.encode())

        # Display the annotated frame
        cv2.imshow("YOLOv8 Inference", results[0].plot())

        # Break the loop if 'q' is pressed
        if cv2.waitKey(1) & 0xFF == ord("q"):
            break
    else:
        # Break the loop if the end of the video is reached
        break

# Release the video capture object and close the display window
ser.close()
cap.release()
cv2.destroyAllWindows()
