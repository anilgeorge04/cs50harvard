var errormsg = document.querySelector('#errormsg');

document.querySelector('form').onsubmit = function () {
    if (document.getElementById('query').value == "") {
        errormsg.textContent = "Can't read your mind here 😞";
        errormsg.style.visibility = "visible";
        window.setTimeout(function () { alert('🤙 Use words master'); }, 1500);
        return false;
    }
    else {
        errormsg.style.visibility = "hidden";
        errormsg.textContent = "";
    }
}