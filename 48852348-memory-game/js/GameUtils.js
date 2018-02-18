.pragma library

function randomShuffle(array) {
  var currentIndex, tmp;
  for (var i = 0; i < array.length; i++) {
    currentIndex = Math.floor(Math.random() * (i + 1));
    tmp = array[i];
    array[i] = array[currentIndex];
    array[currentIndex] = tmp;
  }
}

function generateCardIndexes(imageCount, repeatCount) {
  var cardIndexes = [];
  var i, j;
  for (i = 0; i < imageCount; i++) {
    for (j = 0; j < repeatCount; j++) {
      cardIndexes.push(i + 1);
    }
  }
  randomShuffle(cardIndexes);
  return cardIndexes;
}
