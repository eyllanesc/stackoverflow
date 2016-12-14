from selenium import webdriver

chromedriver= '/usr/bin/chromedriver' #""C:/Users/ndominguez/OneDrive/Executables/chromedriver"
url = "http://app20.susalud.gob.pe:8080/registro-renipress-webapp/listadoEstablecimientosRegistrados.htm?action=mostrarBuscar#"
chrome = webdriver.Chrome(chromedriver)
chrome.get(url)
chrome.execute_script("document.getElementById('datable-grilla-establecimientos-renipress_btnExpAux').click();")
chrome.close()
