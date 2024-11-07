import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Recipes")

    property int _padding : 10

    Column {
        spacing: 10
        padding: 20
        width: parent.width
        height: parent.height

        TextField {
            id: searchField
            placeholderText: "Search for recipes..."
            onAccepted: {
                recipeFetcher.fetchRecipes(text)
            }
        }
        Rectangle{
            width: parent.width - _padding * 2
            height: 600
            anchors.centerIn: parent
            color: "grey"

            ListView {
                id: recipeListView
                width: parent.width
                height: parent.height
                model: recipeModel
                spacing:10
                delegate: Rectangle {
                    width: parent.width
                    height: contentItem.implicitHeight + 20
                    color: "#f9f9f9"
                    border.color: "#d3d3d3"
                    radius: 5
                    clip:true

                    Column {
                        id:contentItem
                        anchors.verticalCenter: parent.verticalCenter

                        Text {
                            text: "Instructions: " + model.id
                            font.pointSize: 10
                            color: "#333"
                            wrapMode: Text.WordWrap
                        }
                        Text {
                            text: model.name
                            font.bold: true
                            font.pointSize: 16
                        }

                        Text {
                            text: model.category + " - " + model.area
                            font.pointSize: 12
                            color: "#666"
                        }

                        Button {
                            text: "download"
                            width: 100
                            height: 50
                            //anchors.horizontalCenter: parent.horizontalCenter
                            //anchors.top: contentItem.bottom

                            // Action à faire quand le bouton est pressé
                            onClicked: {
                                recipeDownloader.fetchAndSaveRecipe(model.id)
                            }
                        }

                        Text {
                            text: "Instructions: " + model.instructions
                            font.pointSize: 10
                            color: "#333"
                            wrapMode: Text.WordWrap
                        }
                    }
                }

            }
        }
    }
    Connections {
        target: recipeFetcher
        function onRecipesFetched(recipes) {
            console.log("--------------------------------")
            console.log("length : "+recipes.length)
            recipeModel.clear();
            for (let i = 0; i < recipes.length; i++) {
                recipeModel.append(recipes[i]);
                console.log("length : "+recipes[i].name)
            }
            console.log("--------------------------------")
        }
    }


    ListModel {
        id: recipeModel
    }
}
