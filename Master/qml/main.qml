import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import Collector 1.0 as Collector
ApplicationWindow{
    id:root
    visible: true
    width: 1400
    height: 480
    title: qsTr("LAN Collector")
    color:"#dfe6e9"
    Timer{
        interval: 3000;
        running: true;
        repeat: true
        onTriggered:{
            Collector.InfoModel.checkAlive();
        }
    }
    Column{
        anchors.fill: parent;
        Rectangle{
            width:parent.width;
            height:12;
            color:"transparent"
        }
        Rectangle{
            width:parent.width;
            height:parent.height;
            color:"transparent"
            Row{
                anchors.fill: parent;
                spacing: 0
                Rectangle{
                    width:15;
                    height:parent.height;
                    color:"transparent"
                }
                Rectangle{
                    id:listRectangle
                    width:parent.width - 30;
                    height:parent.height;
                    color:"transparent"
                    ListView{
                        anchors.fill: parent;
                        model: Collector.InfoModel
                        spacing:10;
                        delegate: Rectangle {
                            height:70
                            width:parent.width;
                            color:"#fff"
                            radius: 20
                            Row{
                                anchors.fill: parent
                                spacing: 0
                                Rectangle{
                                    height:parent.height;
                                    width:15;
                                    color:"transparent"
                                }
                                Rectangle{
                                    width:parent.height;
                                    height:parent.height;
                                    color:"transparent"
                                    Image {
                                        id: robot
                                        width:50
                                        height:50
                                        anchors.centerIn: parent;
                                        fillMode: Image.PreserveAspectFit
                                        source: "/resource/agv.png"
                                    }
                                    ColorOverlay {
                                        id : colorOverlay
                                        anchors.fill: robot
                                        source: robot
                                        color: mAlive ? (mCount ? "#6c5ce7" : "#0984e3") : "#d63031"
                                    }
                                }
                                Rectangle{
                                    height:parent.height;
                                    width:110;
                                    color:"transparent"
                                    Rectangle{
                                        anchors.centerIn: parent;
                                        height:50
                                        width:90
                                        radius: 12
                                        color:"#dfe6e9"
                                        Text{
                                            id : ip_text;
                                            anchors.fill: parent
                                            horizontalAlignment: Text.AlignHCenter
                                            verticalAlignment: Text.AlignVCenter
                                            text: mIP;
                                            font.pixelSize: 40;
                                        }
                                    }
                                }
                                Rectangle{
                                    height:parent.height;
                                    width:2
                                    color:"#aaa"
                                }
                                Rectangle{
                                    height:parent.height;
                                    width:parent.width - parent.height - 15 - 102;
                                    color:"transparent"
                                    Text{
                                        leftPadding: 10
                                        anchors.fill: parent
                                        verticalAlignment: Text.AlignVCenter
                                        text: mInfo;
                                        font.pixelSize: 20;
                                        wrapMode: Text.WordWrap
                                    }
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    width:15;
                    height:parent.height;
                    color:"transparent"
                }
            }
        }
    }
}
