var internalQmlObject = Qt.createQmlObject(
    'import QtQuick 2.5; QtObject{ signal someSignal(int value) }',
    Qt.application, 'InternalQmlObject');
function runNow() {
  console.log(internalQmlObject);
  // internalQmlObject.someSignal(42);
}
