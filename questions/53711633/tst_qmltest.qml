import QtQuick 2.0
import QtTest 1.0

TestCase {
    name: "case_1"
    MouseQml{
        id: mainApp
    }
    function initTestCase() {
        var qmlClear = findChild(mainApp, "clear")
        tryCompare(qmlClear, "text", "Clear")
    }
    function cleanupTestCase() {
    }
    function test_case1() {
        var qmlClear = findChild(mainApp, "clear")
        mouseClick(qmlClear)
    }
    function test_case() {
    }
}
