import QtQuick 2.0

Canvas {
    id:canvas
    onPaint: {
        var ctx = canvas.getContext('2d');
        var originX = 0
        var originY = canvas.height/2
        ctx.save();
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        ctx.translate(originX, originX);
        ctx.globalAlpha = canvas.alpha;
        ctx.strokeStyle = canvas.strokeStyle;
        ctx.fillStyle = canvas.fillStyle;
        ctx.lineWidth = canvas.lineWidth;

        ctx.beginPath();
        ctx.moveTo(75,40);
        ctx.bezierCurveTo(75,37,70,25,50,25);
        ctx.bezierCurveTo(20,25,20,62.5,20,62.5);
        ctx.bezierCurveTo(20,80,40,102,75,120);
        ctx.bezierCurveTo(110,102,130,80,130,62.5);
        ctx.bezierCurveTo(130,62.5,130,25,100,25);
        ctx.bezierCurveTo(85,25,75,37,75,40);
        ctx.closePath();
        ctx.fill();
        ctx.stroke();
        ctx.restore();
    }
}
