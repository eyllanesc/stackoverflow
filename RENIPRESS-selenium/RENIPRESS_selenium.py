import glob
import os
import shutil
from time import sleep

from selenium import webdriver


def clear(directory):
    """
    Elimina todos los archivos del directorio
    :param directory: directorio
    :return:
    """
    os.chdir(directory)
    for file in os.listdir(directory):
        if os.path.isfile(file):
            os.remove(directory + "/" + file)


def save(input_dir, output_dir):
    """
    Mueve los archivos y los enumera: {numero}.xls
    :param input_dir: directorio donde se encuentra el archivo .xls
    :param output_dir: directorio donde se movera el archivo
    :return:
    """
    # espera que exista el archivo, ya que la descarga demora
    while len(glob.glob(input_dir + "/*.xls")) == 0:
        print("waiting")
        sleep(1)

    # creamos la carpeta sino existe
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    # se asume que los archivos estan numerados y tienen el formaro {numero}.xls
    counters = [int(file.replace(".xls", "")) for file in os.listdir(output_dir)]

    # nombre por defecto(0.xls) si la carpeta esta vacia
    name = 0

    # sino sera uno más que el mayor numero
    if counters:
        name = max(counters) + 1

    for src in glob.glob(input_dir + "/*.xls"):
        dst = output_dir + "/" + str(name) + ".xls"
        print(dst)
        # mueve el archivo hacia su destino con el nuevo nombre
        shutil.move(src, dst)


if __name__ == '__main__':
    location = "/home/qhipa/Downloads"
    output_dr = "/home/qhipa/out"

    clear(location)

    chromedriver = '/usr/bin/chromedriver'
    url = "http://app20.susalud.gob.pe:8080/registro-renipress-webapp/listadoEstablecimientosRegistrados.htm" \
          "?action=mostrarBuscar#"
    chrome = webdriver.Chrome(chromedriver)
    chrome.get(url)
    chrome.execute_script("document.getElementById('datable-grilla-establecimientos-renipress_btnExpAux').click();")

    save(location, output_dr)
    chrome.quit()
