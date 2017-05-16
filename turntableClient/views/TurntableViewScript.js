var loaded = false;

function loadItems(container) {
    // Clean children
    for (var i = container.children.length; i > 0; i--) {
        container.children[i-1].destroy()
    }

    // Create items
    var component = Qt.createComponent("TrackImageItem.qml");
    var componentLabel = Qt.createComponent("TrackLabelItem.qml");
    for (var j = 0; j < app.turntable.tracksData.list.length; j++) {
        var item = app.turntable.tracksData.list[j];
        var angle = item.position / app.turntable.nbSteps * -360.0;
        var trackText = app.turntable.tracksData.list[j].name;

        var img = component.createObject(container, {
            "imgAngle": angle,
            "model": item
        });
        img.trackSelected.connect(app.turntable.moveToTrack);

        if (img === null) {
            console.log("Failed to create track img");
        }

        var lab = componentLabel.createObject(container, {
            "imgAngle": angle,
            "trackText": trackText
        });
        if (lab === null) {
            console.log("Failed to create track lab2");
        }
    }
    setOccupiedTracks(container);
}

function setOccupiedTracks(container) {
    for (var i = 0; i < app.turntable.tracksData.list.length; i++) {
        var position = app.turntable.tracksData.list[i].position;
        var img = container.children[i*2];
        if (img === null) {
            console.log("Failed to get trackContainer[" + i + "]");
        }
        else {
            img.occupied = (position === app.turntable.position);
        }
    }
}
