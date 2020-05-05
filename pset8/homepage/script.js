let form = document.getElementById("spam-form");
form.addEventListener("submit", function () {
    days = Math.round(Math.random() * 365);
    alert("Thanks for contacting! You can expect a reply in " + days + " days!");
});