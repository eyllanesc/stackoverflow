SoftwareHEN
==========

El problema que tenia es que cada vez que llenabas un elemento o cambiabas el tamaño del QTableWidget este lanzaba las señales cellChanged, ese código deberia verificar si el elemento existe ya que cuando cambias el tamaño con setRowCount o setColumnCount no creas los items, por lo que algunos pueden estar no creados. 

Solución:

- He desconectado la señal cellChanged de on_Workspace_cellChanged antes de llenar los datos, y despues los conecto nuevamente.(hecho)

- Podrias verificar que exista el item con la siguiente instrucción if(!ui->Workspace->item(i, j)) ya que la función retorna 0 si no existe el item en el slot on_Workspace_cellChanged .(por hacer)