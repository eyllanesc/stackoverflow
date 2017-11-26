var jshelper = parent.jshelper;
console.log(document.getElementById("myBtn"));

document.getElementById("myBtn").addEventListener("click", function(){
    console.log("okay");
    jshelper.pathSelected("Test!");
});