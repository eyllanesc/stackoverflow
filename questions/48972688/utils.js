// https://stackoverflow.com/a/2450976/6622587
function shuffle(model) {
  var currentIndex = model.count, temporaryValue, randomIndex;

  // While there remain elements to shuffle...
  while (0 !== currentIndex) {
    // Pick a remaining element...
    randomIndex = Math.floor(Math.random() * currentIndex)
    currentIndex -= 1
    // And swap it with the current element.
    // the dictionaries maintain their reference so a copy should be made
    // https://stackoverflow.com/a/36645492/6622587
    temporaryValue = JSON.parse(JSON.stringify(model.get(currentIndex)))
    model.set(currentIndex, model.get(randomIndex))
    model.set(randomIndex, temporaryValue);
  }
  return model;
}
