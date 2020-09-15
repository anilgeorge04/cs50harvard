var selectpage = document.getElementById('wishid');

selectpage.onchange = function () {
    var goto = this.value;
    redirect(goto);
}

function redirect(goto) {
    // var conf = confirm("Click OK to go to your magical wish");
    if (goto != '') {
        window.location = goto;
    }
}