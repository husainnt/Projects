Huffman Compression Web App
🚀 Overview
This project is a web-based file compression and decompression tool leveraging Huffman Coding, an efficient algorithm for lossless data compression. The system integrates a Flask backend and an interactive UI built with modern web technologies, including Three.js and GSAP, for a visually engaging experience.
🎯 Features
•	File Compression: Encodes input files into a compressed format using Huffman coding.
•	File Decompression: Restores compressed files back to their original form.
•	Performance Metrics: Displays compression ratio and percentage reduction for evaluation.
•	Futuristic UI: Built with Three.js and GSAP for a stunning 3D effect.
•	Seamless Integration: Frontend and backend work smoothly for a great user experience.
🛠️ Tech Stack
Backend
•	Flask – Python web framework for handling file uploads & processing.
•	Huffman Algorithm – Implemented in C++ for high-speed compression.
Frontend
•	HTML, CSS, JavaScript – Core web technologies.
•	Three.js – For 3D animated backgrounds.
•	GSAP – Smooth animations.
•	Fetch API – Communicates with Flask backend.
📂 Project Structure
Huffman Compression Web-app/
│── huffman-web/
│   │── processed/            # Stores processed files
│   │── static/               # Frontend assets
│   │   │── script.js         # Handles UI interactions & API requests
│   │   │── style.css         # Styling for the web app
│   │── templates/            # HTML templates
│   │   │── index.html        # Main UI page
│   │── uploads/              # Stores uploaded files
│   │── server.py             # Flask backend server
│── huffmancomp.cpp           # Huffman compression C++ program
│── input.txt                 # Sample input file
🏗️ Setup & Installation
1️⃣ Clone the Repository
git clone https://github.com/yourusername/huffman-web.git
cd huffman-web
2️⃣ Set Up a Virtual Environment
python -m venv venv
source venv/bin/activate  # On Windows: venv\Scripts\activate
3️⃣ Install Dependencies
pip install flask
4️⃣ Run the Server
python server.py
5️⃣ Open in Browser
Visit: http://127.0.0.1:5000
📸 Screenshots
 ![hmweb](https://github.com/user-attachments/assets/4e3e14fc-1db1-4182-82b4-19ebc991238e)
🤝 Contributing
Feel free to fork this repository, open an issue, or submit a pull request to contribute!
📜 License
This project is licensed under the MIT License.
________________________________________
⭐ If you liked this project, give it a star on GitHub! ⭐

