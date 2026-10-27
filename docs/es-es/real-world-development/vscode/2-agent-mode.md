---
title: "Ejercicio 2 - Añadir funcionalidades con el modo agente de Copilot"
authors:
  - geektrainer
lastUpdated: 2026-06-30
---

Incluso los cambios más sencillos de una aplicación suelen afectar a varios archivos y requieren tareas como ejecutar pruebas. Normalmente hay que localizar los archivos, hacer los cambios, ejecutar las pruebas, depurar, averiguar qué archivo falta y volver a modificarlo. La lista no acaba.

Para eso sirve el modo agente de Copilot.

El modo agente de Copilot puede trabajar de forma más autónoma en el IDE. Se comporta de forma parecida a un desarrollador: explora la estructura del proyecto, realiza los cambios necesarios, ejecuta tareas como las pruebas y corrige automáticamente los errores que encuentra. En este ejercicio usarás el modo agente para añadir funcionalidades al sitio.

> [!NOTE]
> Aunque los nombres se parecen, el modo agente y el agente en la nube ofrecen experiencias distintas. El modo agente trabaja en tu IDE y permite ciclos de respuesta rápidos e interacción directa. El agente en la nube trabaja de forma asíncrona como un compañero del equipo e interactúa contigo mediante incidencias y solicitudes de incorporación de cambios.

En este ejercicio aprenderás cómo:

- el modo agente de Copilot explora el proyecto, identifica los archivos relevantes y coordina los cambios;
- el modo agente implementa funcionalidades en la interfaz y la capa de datos;
- revisar los cambios y las pruebas generados por el modo agente antes de fusionarlos.

## Escenario

A medida que crece la lista de juegos, quieres permitir que los usuarios filtren por categoría y editorial. En el ejercicio anterior ya has añadido un helper de editoriales. Ahora completarás el trabajo restante en la capa de datos, la interfaz y las pruebas con el modo agente de Copilot.

## Ejecutar el sitio web de Tailspin Toys

Antes de hacer cambios, explora el sitio para entender su funcionalidad actual.

Tailspin Toys es una plataforma de financiación colectiva de juegos de mesa con una temática de desarrollo. Permite mostrar juegos y sus detalles. El sitio es una aplicación Astro que genera páginas HTML estáticas durante la compilación. Las páginas consultan directamente una base de datos SQLite local mediante Drizzle ORM en su frontmatter; no hay una API de backend independiente ni un framework de interfaz en el cliente. Los helpers reutilizables de acceso a datos se encuentran en `src/lib/`, y la interactividad se implementa con scripts Astro pequeños y acotados que usan las API DOM estándar.

### Iniciar el sitio web

La tarea `npm run dev` inicia el único servidor de desarrollo de Astro. Para ejecutarlo en Codespaces:

1. Vuelve a tu Codespace. Después del ejercicio anterior deberías estar en `main`.
2. Abre un terminal con <kbd>Control</kbd>+<kbd>\`</kbd> (Mac) o <kbd>Ctrl</kbd>+<kbd>\`</kbd> (Windows/Linux).
3. Crea y selecciona una rama para el filtrado:

   ```bash
   git checkout main
   git pull
   git checkout -b filtering-vscode
   ```

4. Inicia el sitio:

   ```bash
   npm run dev
   ```

   Cuando el servidor de Astro esté listo, aparecerá un mensaje con la URL, parecido a este:

   ```bash
   🚀 Tailspin Toys is ready!
      Astro server: http://localhost:4321
      Press Ctrl-C to stop.
   ```

> [!NOTE]
> Si aparece un cuadro de diálogo para abrir `http://localhost:4321` en un navegador, ciérralo seleccionando **x**.

5. Abre el sitio manteniendo pulsada la tecla <kbd>Command</kbd> (Mac) o <kbd>Ctrl</kbd> (Windows/Linux) y seleccionando la dirección del servidor Astro `http://localhost:4321` en el terminal.

> [!NOTE]
> En un codespace, al seleccionar el vínculo de localhost en el terminal, se redirige a `https://<your-codespace-name>-4321.app.github.dev/`. Es un túnel privado al servidor web que se ejecuta en tu codespace.

### Explorar el sitio web

Mientras se ejecuta el sitio, explora sus funciones principales:

- **Página de inicio**: muestra juegos de mesa con sus títulos, imágenes y descripciones.
- **Página de detalles del juego**: al seleccionar un juego, se abre una página con más información, como el título, la descripción, la editorial y la categoría.

## Explorar el backlog con Copilot

> [!TIP]
> **Abrir Copilot Chat**
>
> Antes de empezar, vuelve al codespace, abre el panel Copilot Chat y selecciona **New Chat** para iniciar una conversación nueva. El modo y el modelo varían según el ejercicio; cada paso lo indicará cuando sea relevante.

El sitio funciona, pero queremos ampliarlo. Primero revisaremos el backlog. Al crear el proyecto a partir de la plantilla, se generaron incidencias automáticamente. Pide a GitHub Copilot que las muestre:

1. En el selector de agentes de Chat, selecciona **Agent**. El agente planifica e implementa cambios en varios archivos, ejecuta comandos de terminal y usa herramientas.

   ![Selector de agentes en la vista Chat.](../../../_images/shared-chat-mode-selector.png)

2. Selecciona **Claude Sonnet 4.5** en la lista de modelos disponibles.

> [!CAUTION]
> Los autores no recomiendan un modelo concreto. Al preparar el taller usamos Claude Sonnet 4.5 y lo indicamos para que las sugerencias fueran relativamente coherentes y la experiencia resultara sencilla. Como los LLM son probabilísticos, las sugerencias pueden diferir de las descritas; es normal.

> [!NOTE]
> Por su naturaleza probabilística, Copilot puede usar un comando MCP diferente, pero debería completar la tarea.

3. Pide a Copilot que muestre las incidencias del backlog:

   ```plaintext
   Please show me the backlog of items from my GitHub repository. Help me prioritize them based on those which will be most useful to the user.
   ```

4. Selecciona **Continue** para ejecutar el comando que enumera las incidencias.
5. Revisa la lista generada.

Observa cómo Copilot prioriza las incidencias según la utilidad que podrían tener para los usuarios.

## Revisar los archivos de instrucciones

Antes de pedir al agente que genere código, revisa el archivo de instrucciones que usarás para proporcionar contexto a Copilot. El archivo [de instrucciones de interfaz][ui-instructions] explica cómo añadir funcionalidades al sitio.

1. En el codespace, abre `.github/instructions/ui.instructions.md`.
2. Observa las directrices generales, entre ellas:
   - una descripción de la arquitectura;
   - principios de diseño de componentes, pruebas y accesibilidad;
   - enlaces a archivos de instrucciones para Astro, Tailwind CSS y Drizzle.

> [!TIP]
> Los archivos de instrucciones pueden enlazar tanto a otros archivos de instrucciones como a archivos del proyecto. Las rutas son relativas al archivo de instrucciones. Así puedes reutilizar y dividir instrucciones grandes en archivos más pequeños, además de mostrar ejemplos que Copilot puede seguir.

## Implementar el filtrado

Para completar el filtrado hacen falta al menos tres cambios:

- añadir o ajustar la lógica de filtrado en la capa de datos (`src/lib/`);
- añadir o actualizar las pruebas del comportamiento;
- actualizar la página de listado de juegos para incluir la interfaz de filtrado.

También hay que ejecutar las pruebas y confirmar que pasan antes de fusionar los cambios. El modo agente puede encargarse de estas tareas.

1. Continúa la conversación actual con Copilot o selecciona **New Chat**.
2. Selecciona **Add Context**, **Instructions** y **ui** para añadir el archivo de instrucciones.

   ![Ejemplo de selección del archivo de instrucciones de interfaz](../../../_images/ex3-select-instructions-file.png)

3. Confirma que **Agent** sigue seleccionado.

   ![Selector de agentes en la vista Chat.](../../../_images/shared-chat-mode-selector.png)

4. Confirma que sigue seleccionado el modelo **Claude Sonnet 4.5**.
5. Pide a Copilot que implemente la funcionalidad según la incidencia del backlog:

   ```plaintext
   Please update the site to include filtering by publisher and category based on the requirements from the related GitHub issue in the backlog. A publishers helper already exists from the previous exercise, so preserve and refine that work as needed while completing the remaining data-layer, UI, and tests. Ensure all tests are passing before completion. The server is already running, so you do not need to start it up.
   ```

6. Copilot explorará el proyecto para localizar los archivos de la funcionalidad en la capa de datos, la interfaz y las pruebas. Después modificará los archivos y ejecutará las pruebas.

   ![Copilot explora los archivos del proyecto](../../../_images/ex3-agent-mode-explores.png)

> [!NOTE]
> Copilot explorará el proyecto, modificará archivos y ejecutará tareas. El proceso puede tardar varios minutos. Mientras trabaja, pueden aparecer los controles **Keep** y **Undo** en el editor. No tienes que seleccionarlos mientras Copilot siga trabajando; al terminar podrás aceptar o deshacer los cambios.

7. Cuando Copilot te lo pida, selecciona **Continue** para ejecutar las pruebas.

   ![Cuadro de diálogo en Copilot Chat que solicita confirmación para ejecutar pruebas](../../../_images/ex3-agent-mode-run-tests.png)

8. Puede que haya pausas y que algunas pruebas fallen durante el proceso. Copilot alternará entre la generación de código y las pruebas hasta completar la tarea sin detectar errores.

   ![Sesión completa de Copilot Agent Mode en Chat](../../../_images/ex3-agent-mode-proposed-changes.png)

9. Examina el código generado para detectar posibles problemas.

> [!CAUTION]
> Es importante revisar siempre el código generado por Copilot o cualquier otra herramienta de IA.

10. Vuelve al navegador donde se ejecuta el sitio y explora la nueva funcionalidad.
11. Cuando hayas confirmado que funciona y revisado el código, selecciona **Keep** en Copilot Chat.

## Resumen y siguientes pasos

¡Has usado el modo agente de GitHub Copilot para añadir funcionalidades a Tailspin Toys! Has aprendido cómo:

- el modo agente implementa funcionalidades en la interfaz y la capa de datos;
- el modo agente explora el proyecto, identifica archivos y coordina cambios;
- revisar los cambios y las pruebas generados antes de fusionarlos.

A continuación, [probarás la funcionalidad con el servidor Playwright MCP][next-lesson] y abrirás una solicitud de incorporación de cambios.

### Ejercicio de ampliación: implementar la paginación

A medida que crezca la lista de juegos, será necesario paginarla. Usa lo aprendido para pedir a Copilot que añada la paginación. Al preparar el prompt:

- sigue las prácticas recomendadas y usa los archivos de instrucciones existentes;
- decide cómo debe funcionar la paginación: por ejemplo, si el usuario podrá seleccionar el tamaño de página o si será fijo;
- proporciona a Copilot las directrices necesarias para implementar el comportamiento que quieres;
- itera con Copilot y proporciona más contexto cuando haga falta. Es lo habitual al trabajar con Copilot.

## Recursos

- [Modos ask, edit y agent de Copilot: qué hacen y cuándo usarlos][choose-mode]
- [Modo agente en VS Code][vs-code-agent-mode]

[previous-lesson]: ../1-custom-instructions/
[next-lesson]: ../3-mcp/
[ui-instructions]: https://github.com/github-samples/tailspin-toys/blob/main/.github/instructions/ui.instructions.md
[choose-mode]: https://github.blog/ai-and-ml/github-copilot/copilot-ask-edit-and-agent-modes-what-they-do-and-when-to-use-them/
[vs-code-agent-mode]: https://code.visualstudio.com/docs/copilot/chat/chat-agent-mode
