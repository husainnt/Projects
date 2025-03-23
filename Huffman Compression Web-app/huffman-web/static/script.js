document.addEventListener("DOMContentLoaded", function () {
    const form = document.querySelector("form");
    const message = document.getElementById("message");
    const uploadBtn = document.getElementById("upload-btn");
    const fileInput = document.getElementById("file-input");

   
    form.addEventListener("submit", async function (event) {
        event.preventDefault();
        const formData = new FormData(form);

        try {
            const response = await fetch("/", {
                method: "POST",
                body: formData
            });

            const result = await response.json();
            showMessage(result.success ? "success" : "error", result.message);
        } catch (error) {
            showMessage("error", error.message);
        }
    });

   
    function showMessage(type, text) {
        message.innerHTML = text;
        message.style.color = type === "success" ? "lime" : "red";
        gsap.fromTo(message, { opacity: 0, scale: 0.8 }, { opacity: 1, scale: 1.1, duration: 0.3 });

        if (type === "error") {
            gsap.to(message, { x: -5, repeat: 5, yoyo: true, duration: 0.1 });
        }
    }

    uploadBtn.addEventListener("click", () => fileInput.click());

    uploadBtn.addEventListener("dragover", (event) => {
        event.preventDefault();
        uploadBtn.style.background = "rgba(0, 255, 255, 0.2)";
    });

    uploadBtn.addEventListener("dragleave", () => {
        uploadBtn.style.background = "transparent";
    });

    uploadBtn.addEventListener("drop", (event) => {
        event.preventDefault();
        fileInput.files = event.dataTransfer.files;
        uploadBtn.textContent = `📂 ${fileInput.files[0].name}`;
    });

  
    const scene = new THREE.Scene();
    const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
    const renderer = new THREE.WebGLRenderer({ canvas: document.getElementById("bg"), alpha: true });

    renderer.setSize(window.innerWidth, window.innerHeight);
    document.body.appendChild(renderer.domElement);

    const starGeometry = new THREE.BufferGeometry();
    const starVertices = [];

    for (let i = 0; i < 600; i++) {
        starVertices.push((Math.random() - 0.5) * 2000, (Math.random() - 0.5) * 2000, (Math.random() - 0.5) * 2000);
    }

    starGeometry.setAttribute("position", new THREE.Float32BufferAttribute(starVertices, 3));
    const starMaterial = new THREE.PointsMaterial({ color: 0x00ffff, size: 3, blending: THREE.AdditiveBlending });

    const stars = new THREE.Points(starGeometry, starMaterial);
    scene.add(stars);
    camera.position.z = 500;

    function animateStars() {
        requestAnimationFrame(animateStars);
        stars.rotation.y += 0.002;
        renderer.render(scene, camera);
    }

    animateStars();
});