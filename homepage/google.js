var errormsg = document.getElementById('error');

document.getElementById('form').onsubmit = function () {
    if (document.getElementById('query') == "") {
        errormsg.innerHTML = "Please enter a query";
    }
    else {
        errormsg.innerHTML = "";
    }
}