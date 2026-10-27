---
title: "Ejercicio 0: Requisitos previos"
authors:
  - geektrainer
lastUpdated: 2026-06-30
---

Antes de empezar los ejercicios de VS Code, prepara todo lo necesario. Crearás una copia propia del repositorio Tailspin Toys, iniciarás un [codespace][codespaces] para trabajar y comprobarás que GitHub Copilot Chat funciona en el editor.

## Configurar el repositorio del laboratorio

Para crear una copia del repositorio en la que trabajarás, crearás una instancia a partir de la [plantilla][template-repository]. Incluirá todos los archivos necesarios para el laboratorio.

1. En una ventana nueva del navegador, abre la [plantilla de Tailspin Toys][tailspin-template].
2. Crea una copia seleccionando el botón **Use this template** en la página del repositorio y, después, **Create a new repository**.

    ![Botón Use this template](../../../_images/ex0-use-template.png)

3. Si participas en un evento organizado por GitHub o Microsoft, sigue las instrucciones de los mentores. En caso contrario, crea el repositorio nuevo en una organización donde tengas acceso a GitHub Copilot.

    ![Configuración del repositorio basado en una plantilla](../../../_images/ex0-repository-settings.png)

4. Anota la ruta del repositorio que has creado (**organization-or-user-name/repository-name**); la necesitarás más adelante.

> [!NOTE]
> **El backlog está preparado**
>
> Al crear el repositorio a partir de la plantilla, se crea automáticamente un backlog de incidencias de GitHub. Trabajarás con ellas durante el taller; no tienes que registrar ninguna.

## Crear un codespace

A continuación, usarás un codespace para completar los ejercicios del laboratorio.

[GitHub Codespaces][codespaces] es un entorno de desarrollo en la nube que permite escribir, ejecutar y depurar código en el navegador. Ofrece un IDE completo con compatibilidad con varios lenguajes de programación, extensiones y herramientas.

1. Abre el repositorio que acabas de crear.
2. Selecciona el botón verde **Code**.

    ![Botón Code](../../../_images/ex0-code-button.png)

3. Selecciona la pestaña **Codespaces** y, después, el botón **+** para crear un codespace.

    ![Crear un codespace](../../../_images/ex0-create-codespace.png)

La creación del codespace tardará unos minutos, aunque será mucho más rápida que instalar todos los servicios manualmente. Mientras tanto, puedes explorar otras funciones de GitHub Copilot, que veremos a continuación.

> [!CAUTION]
> Volverás al codespace en un ejercicio posterior. Por ahora, déjalo abierto en una pestaña del navegador.

> [!NOTE]
> Este taller está preparado para ejecutarse en un codespace o en un [contenedor de desarrollo][dev-containers] local. Ambos entornos incluyen los requisitos necesarios. Si prefieres trabajar localmente, abre el repositorio clonado en VS Code y selecciona **Reopen in Container** cuando se te solicite. VS Code creará el mismo contenedor de desarrollo que usa el codespace.

[codespaces]: https://github.com/features/codespaces
[dev-containers]: https://code.visualstudio.com/docs/devcontainers/containers

## Usar GitHub Copilot Chat y el modo agente

Para acceder al modo agente de GitHub Copilot Chat, debes tener instalada la extensión GitHub Copilot Chat en el IDE. Si usas un codespace de GitHub, ya debería estar instalada.

> [!TIP]
> Si no tienes la extensión, puedes [instalarla desde Visual Studio Code Marketplace][copilot-chat-extension]. También puedes abrir la vista Extensions de Visual Studio Code, buscar **GitHub Copilot Chat** y seleccionar **Install**.

Una vez instalada la extensión, puede que tengas que autenticarte con tu cuenta de GitHub.

1. Vuelve a tu codespace.
2. Si Copilot Chat no aparece a la derecha del editor, selecciona el icono **Copilot Chat** en la parte superior del codespace.
3. Escribe un mensaje como «Hello world» en la ventana de Copilot Chat y pulsa Intro. Así se iniciará Copilot Chat.
4. Si todavía no te has autenticado, se te pedirá que inicies sesión en GitHub. Sigue las instrucciones para autenticarte.

    ![Ejemplo de un mensaje para autenticarse en Copilot Chat](../../../_images/ex1-copilot-authentication.png)

5. Después de autenticarte, verás la ventana de Copilot Chat.

## Resumen

¡Has creado una copia del repositorio del laboratorio! También has iniciado la creación del codespace que usarás cuando empieces a escribir código.

## Siguiente paso

Empecemos a trabajar con Copilot. Continúa con el [Ejercicio 1: Instrucciones personalizadas][next-lesson], donde enseñarás a Copilot las convenciones del proyecto.

## Recursos

- [Introducción a GitHub Codespaces][codespaces]
- [Crear un repositorio a partir de una plantilla][template-repository]
- [Inicio rápido de Codespaces][codespaces-quickstart]

[tailspin-template]: https://github.com/github-samples/tailspin-toys
[template-repository]: https://docs.github.com/repositories/creating-and-managing-repositories/creating-a-template-repository
[codespaces-quickstart]: https://docs.github.com/codespaces/getting-started/quickstart
[copilot-chat-extension]: https://marketplace.visualstudio.com/items?itemName=GitHub.copilot-chat
[next-lesson]: ../1-custom-instructions/
