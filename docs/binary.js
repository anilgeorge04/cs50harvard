var selectguide = document.getElementById('guide');
var displayfield = document.querySelector('#guess');
var guess = 0, count = 0, start = 1, end = 249;

// Turn display on
function startGame() {
    document.getElementById('game-field').style.visibility = 'visible';
    guess = guessNum(selectguide.value);
    display(guess);
}

// Restart game
function resetGame() {
    document.getElementById('game-field').style.visibility = 'hidden';
    guess = 0;
    count = 0;
    start = 1;
    end = 249;
}

// Guess number using drop-down
function guessNum(guideVal) {
    if (count < 8) { count++; } else { count = 8; }
    if (guideVal == "") { return 125; }
    else if (guideVal == "go-high") { start = guess + 1; }
    else if (guideVal == "go-low") { end = guess - 1; }
    else {
        if (count == 1) { alert("Right in the first guess, wow! 🎆"); }
        else { alert(count - 1 + " guesses. Yay! 🎆"); }
        resetGame();
    }
    guess = Math.round((start + end) / 2);
    return guess;
}

selectguide.onchange = function () {
    guess = guessNum(this.value);
    display(guess);
    selectguide.selectedIndex = 0;
}

function display(displayGuess) {
    displayfield.innerHTML = displayGuess;
}
