import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtPositioning 5.12
import QtQuick.Layouts 1.0
import QtLocation 5.12

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("QmlZooMapApp")

    GridLayout {
        anchors.fill: parent

        ComboBox {
            id: mapChoose

            model: ListModel {}

            onCurrentIndexChanged: {
                the_map.activeMapType = the_map.supportedMapTypes[mapChoose.currentIndex]
            }

            Layout.row: 0
            Layout.column: 0
            Layout.fillWidth: true
            Layout.fillHeight: false
        }

        Map {
            id: the_map
            minimumZoomLevel: 3
            maximumZoomLevel: 16
            zoomLevel: 10
            center: QtPositioning.coordinate(30.67, 104.06)

            plugin: Plugin {
                name: "qmlzoomap"

                PluginParameter {
                    name: "service"
                    value: "google_map"
                }

                PluginParameter {
                    name: "format"
                    value: "png"
                }
            }

            Layout.row: 1
            Layout.column: 0
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    Component.onCompleted: {
        for (var i = 0; i < the_map.supportedMapTypes.length; ++i) {
            var type = the_map.supportedMapTypes[i]

            mapChoose.model.append({text: type.name})
        }

        mapChoose.currentIndex = 0
    }
}
