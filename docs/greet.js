function greet() {
    var userName = document.querySelector('#name');
    var display = document.querySelector('#disp-msg');
    if (userName.value != '') {
        var msg = '. It is my greatest honor to serve you!';
        display.textContent = 'Hello, Master ' + userName.value + msg;
        display.className = 'disp-success'
    }
    display.style.visibility = 'visible';
    userName.innerHTML = '';
}
