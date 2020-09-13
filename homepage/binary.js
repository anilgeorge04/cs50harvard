var selectguide = document.getElementById('guide');
var displayfield = document.querySelector('#guess');
var guess = 0, count = 0, start = 1, end = 249;

// Turn display on
function startGame() {
    document.getElementById('game-field').style.visibility = 'visible';
    guess = selectguide.value;
    // display(guess);
}

// function guessNum(guideVal) {
//     // successMsg = "Success 🎆 in " + count-1 + "guesses!"
//         document.getelementbyid('guess').innerhtml = guideVal;
//     count++;
//     if (guideVal == "") { return 125; }
//     else if (guideVal == "go-high") { start = guess + 1; }
//     else if (guideVal == "go-low") { end = guess - 1; }
//     else { return 100; }
//     guess = Math.round((start + end) / 2);
//     return guess;
// }

// selectguide.onchange = function () {
//     displayfield.innerHTML = "change";
//     // guess = guessnum(this.value);
//     // display(guess);
// }

// function display(displayGuess) {
//     document.getelementbyid('guess').innerhtml = displayGuess;
// }
