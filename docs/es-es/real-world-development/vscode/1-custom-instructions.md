---
title: "Ejercicio 1 - Instrucciones personalizadas (VS Code)"
authors:
  - geektrainer
lastUpdated: 2026-06-30
---

[← Lección anterior: Requisitos previos][previous-lesson] · [Siguiente lección: Modo agente →][next-lesson]

El contexto es clave cuando se trabaja con IA generativa. Si una tarea debe realizarse de una forma concreta, o Copilot necesita información de fondo, debes asegurarte de que pueda acceder a ese contexto. Los [archivos de instrucciones][instruction-files] son una de las principales formas de proporcionar directrices para generar código.

En este ejercicio:

- explorarás cómo llegan a Copilot el contexto del proyecto, las directrices de desarrollo y los estándares de documentación mediante las instrucciones personalizadas del repositorio y los archivos con ámbito de ruta;
- generarás el primer bloque de datos para el filtrado (un helper de editoriales) con las instrucciones *actuales*;
- añadirás un estándar general al archivo `.github/copilot-instructions.md`;
- volverás a ejecutar el mismo prompt y observarás cómo el código generado sigue el nuevo estándar;
- confirmarás los cambios de las instrucciones y del filtrado en `main` para que Copilot pueda usar las directrices actualizadas en el siguiente ejercicio.

> [!CAUTION]
> El código generado puede no seguir todos los estándares que hayas definido. Copilot no es determinista. El objetivo es observar la *tendencia* del cambio de comportamiento tras actualizar las instrucciones, no obtener siempre un resultado idéntico.

## Archivos de instrucciones

### Escenario

Tailspin Toys tiene directrices y requisitos para sus prácticas de desarrollo:

- La capa de datos siempre necesita pruebas unitarias.
- La interfaz debe estar en modo oscuro y tener un aspecto moderno.
- El código debe incluir documentación en forma de comentarios TSDoc.
- Cada archivo debe empezar con un bloque de comentarios que describa su función.

Usarás archivos de instrucciones para proporcionar a Copilot la información necesaria para trabajar de acuerdo con estas prácticas.

### Instrucciones personalizadas

Las instrucciones personalizadas proporcionan a Copilot contexto y preferencias para que entienda mejor tu estilo de desarrollo y tus requisitos. Puedes especificar las convenciones, las bibliotecas y los comentarios que prefieras. Puedes crear instrucciones para todo el repositorio o para tipos concretos de archivos y tareas.

Hay dos tipos de archivos de instrucciones:

- `.github/copilot-instructions.md` es un único archivo que se envía a Copilot en **todas** las solicitudes del repositorio. Debe contener información general del proyecto relevante para la mayoría de las solicitudes de chat o CLI, como la pila tecnológica, una descripción del proyecto, buenas prácticas y directrices globales.
- `.github/instructions/*.instructions.md` contiene instrucciones para tareas o tipos de archivo concretos, como TypeScript, Astro, componentes de interfaz o pruebas unitarias.

> [!NOTE]
> En el IDE, los archivos de instrucciones se usan para generar código en Copilot Chat, no para completar código ni para sugerir la siguiente edición.
>
> Copilot Chat, Copilot CLI y Copilot cloud agent usan las instrucciones del repositorio y los archivos `*.instructions.md` que tienen frontmatter `applyTo`.
>
> Copilot también [admite otros formatos de archivos de instrucciones][custom-instructions-support], como AGENTS.md y CLAUDE.md.

### Buenas prácticas para gestionar archivos de instrucciones

El proyecto de ejemplo muestra un enfoque posible:

- Mantén `copilot-instructions.md` centrado en directrices del proyecto, como su descripción, estructura y estándares globales.
- Usa `*.instructions.md` para tipos de archivo (pruebas unitarias, componentes Astro, capa de datos) o tareas concretas.
- Escribe en lenguaje natural, con directrices claras y ejemplos de código correctos e incorrectos.

No existe una única forma de crear archivos de instrucciones ni de usar la IA. La experimentación te ayudará a encontrar la solución adecuada para tu proyecto.

> [!TIP]
> Los proyectos que usan GitHub Copilot deberían disponer de una colección completa de archivos de instrucciones. En este proyecto encontrarás archivos para varios tipos de tareas, incluidas las [actualizaciones de interfaz][ui-instructions] y [Astro][astro-instructions].
>
> Copilot también puede generar archivos de instrucciones. Cada entorno ofrece esta opción de forma diferente (por ejemplo, **Configure Chat → Generate Agent Instructions** en VS Code o `/init` en Copilot CLI). La lección correspondiente indicará cuándo usarla.
>
> Para buscar plantillas o ideas, explora [awesome-copilot][awesome-copilot], un repositorio de instrucciones, agentes personalizados y otros recursos.

[ui-instructions]: https://github.com/github-samples/tailspin-toys/blob/main/.github/instructions/ui.instructions.md
[astro-instructions]: https://github.com/github-samples/tailspin-toys/blob/main/.github/instructions/astro.instructions.md
[awesome-copilot]: https://github.com/github/awesome-copilot
[custom-instructions-support]: https://docs.github.com/copilot/reference/custom-instructions-support

## Explorar los archivos de instrucciones personalizadas del proyecto

Lee los archivos de instrucciones incluidos en el repositorio: `.github/copilot-instructions.md` y varios archivos `*.instructions.md`. Ábrelos en el editor o en la interfaz web de GitHub.

1. Abre `.github/copilot-instructions.md`.
2. Explora la breve descripción del proyecto y las secciones **Agent notes**, **Code standards**, **Scripts** y **Repository Structure**. En **Code standards**, observa las directrices anidadas para **GitHub Actions Workflows**. Se aplican a cualquier interacción con Copilot.
3. Explora `.github/instructions`. Hay instrucciones para Astro, la capa de datos Drizzle, pruebas y otros ámbitos.
4. Abre `.github/instructions/unit-tests.instructions.md`. El campo `applyTo` del principio define el patrón (relativo a la raíz del repositorio) que determina los archivos a los que se aplican las instrucciones; por ejemplo, los archivos TypeScript de pruebas que coincidan con `**/*.test.ts`.
5. Observa las instrucciones específicas para crear pruebas unitarias.
6. Abre `.github/instructions/drizzle.instructions.md` y ve al final. Observa los enlaces a otros archivos, como `unit-tests.instructions.md`, y a archivos existentes. Las rutas son relativas al archivo de instrucciones.

> [!NOTE]
> La sección **Code formatting requirements** de `copilot-instructions.md` describe los estándares del proyecto, pero todavía no exige documentación en el código. En los pasos siguientes añadirás directrices sobre los comentarios TSDoc y los encabezados de comentario de los archivos.

## Crear una rama para los cambios

Sigue estas prácticas recomendadas y crea una rama para los cambios:

1. Vuelve al codespace del ejercicio anterior.
2. Abre un terminal con <kbd>Control</kbd>+<kbd>`</kbd> (Mac) o <kbd>Ctrl</kbd>+<kbd>`</kbd> (Windows/Linux).
3. Crea una rama y cámbiate a ella:

   ```bash
   git checkout -b custom-instructions
   ```

## Usar Copilot Chat *antes* de actualizar las instrucciones

> [!TIP]
> **Abrir Copilot Chat**
>
> Antes de empezar, vuelve al codespace, abre el panel Copilot Chat y selecciona **New Chat** para iniciar una conversación nueva. El modo y el modelo varían según el ejercicio; cada paso lo indicará cuando sea relevante.

Primero envía un prompt con las instrucciones actuales. Más adelante las actualizarás y volverás a enviar el mismo prompt para comparar el resultado.

1. Cierra las pestañas abiertas de ejercicios anteriores para que Copilot use solo el contexto necesario.
2. Abre `src/lib/publishers.ts` para indicar dónde debe ubicarse el helper.
3. En el selector de agentes de Chat, selecciona **Agent** para que Copilot pueda aplicar cambios.

   ![Selector de agentes en la vista Chat.](../../../_images/shared-chat-mode-selector.png)

4. Envía este prompt:

   ```plaintext
   Create or update src/lib/publishers.ts with a data-access helper that returns a list of all publishers with the name and id for each. Apply the file changes.
   ```

5. Copilot explorará el proyecto y aplicará cambios, posiblemente al helper y a sus pruebas.
6. Observa que el helper propuesto es una función tipada que recibe un cliente `db` y devuelve una matriz tipada de editoriales; sigue las convenciones de la capa de datos de `.github/instructions/drizzle.instructions.md`, que se aplica a `src/lib/*.ts`.
7. Observa que al código propuesto le faltan los comentarios TSDoc y el encabezado de comentario del archivo.

> [!CAUTION]
> Como Copilot es probabilístico, puede que añada comentarios de documentación aunque no se lo hayas pedido. No pasa nada; lo importante es observar la mejora de coherencia después de actualizar las instrucciones.

## Añadir un estándar para todo el repositorio

El archivo `.github/copilot-instructions.md` proporciona información general del proyecto. Añade los estándares necesarios para mejorar las sugerencias de código.

1. Vuelve a abrir `.github/copilot-instructions.md`.
2. Localiza **Code formatting requirements**, cerca de la línea 27. Verás que todavía no exige documentación en el código.
3. Añade estas líneas de Markdown debajo de los estándares existentes:

   ```markdown
   - Every exported function should have a TSDoc comment describing its purpose, parameters, and return value.
   - Before imports or any code, add a comment block to the file that explains its purpose.
   ```

4. Guarda `copilot-instructions.md`.

> [!TIP]
> Como has visto en la lección anterior, puedes crear instrucciones en `.github/copilot-instructions.md` para todo el repositorio o en archivos `*.instructions.md` para lenguajes, tipos de archivo o tareas concretas. El archivo general es adecuado para estándares como los comentarios de documentación.

## Volver a ejecutar el prompt y observar el cambio

1. Vuelve a Copilot Chat y selecciona **New Chat** para borrar el contexto anterior.
2. Selecciona `src/lib/publishers.ts` para indicar a Copilot en qué archivo trabajar.
3. Envía el mismo prompt:

   ```plaintext
   Create or update src/lib/publishers.ts with a data-access helper that returns a list of all publishers with the name and id for each. Apply the file changes.
   ```

4. Observa que el archivo propuesto ahora empieza con un bloque de comentarios parecido a este:

   ```typescript
   /**
    * Publisher data-access helpers for the Tailspin Toys Crowd Funding platform.
    * Provides functions to retrieve publisher information from the database.
    */
   ```

5. Observa que la función propuesta incluye un comentario TSDoc similar al siguiente:

   ```typescript
   /**
    * Returns a list of all publishers with their id and name.
    *
    * @param db - The Drizzle database client.
    * @returns A promise that resolves to an array of publisher objects.
    */
   ```

Has guiado a Copilot para que aplique un estándar nuevo al código real que utilizarás en el ejercicio siguiente.

## Confirmar las instrucciones y enviar la rama

Los archivos de instrucciones se gestionan con control de código fuente, como cualquier otro archivo.

1. Abre un terminal con <kbd>Control</kbd>+<kbd>`</kbd> (Mac) o <kbd>Ctrl</kbd>+<kbd>`</kbd> (Windows/Linux).
2. Confirma que los cambios están presentes:

   ```bash
   git status
   ```

3. Prepara y confirma las instrucciones y todos los archivos que Copilot haya modificado para el helper:

   ```bash
   git add .github/copilot-instructions.md src/lib/publishers.ts
   # Si git status muestra otros cambios relacionados, como pruebas, añádelos también.
   git commit -m "Add doc comment standards and publishers helper foundation"
   ```

4. Envía la rama al repositorio:

   ```bash
   git push -u origin custom-instructions
   ```

## Crear y fusionar una solicitud de incorporación de cambios

Después de enviar la rama, crea una PR asociada a la incidencia del backlog sobre la actualización de las instrucciones. Copilot puede buscar la incidencia, crear la PR y fusionarla.

> [!NOTE]
> En este ejercicio Copilot actuará por primera vez en GitHub. La plantilla del proyecto ya configura las herramientas de GitHub. Puede que VS Code te pida iniciar sesión la primera vez que Copilot use una herramienta; sigue las instrucciones. En un ejercicio posterior aprenderás cómo funciona esta conexión mediante Model Context Protocol.

1. Abre Copilot Chat en el codespace.
2. Pulsa <kbd>Control</kbd>+<kbd>Command</kbd>+<kbd>I</kbd> (Mac) o <kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>I</kbd> (Windows/Linux) para abrir la vista Copilot Chat y confirma que **Agent** está seleccionado.
3. Pide a Copilot que busque la incidencia sobre la actualización de los archivos de instrucciones y cree una PR desde la rama actual, indicando que la cierra y que también se ha añadido el helper de editoriales:

   ```plaintext
   Find the issue related to updating the instructions file. Create a new PR from the current branch, highlight that the PR closes that issue, and include that we also added the publishers helper foundation for the upcoming filtering work.
   ```

4. Copilot buscará la incidencia y creará la PR.
5. Cuando Copilot te pida permiso para realizar acciones en GitHub, revisa la solicitud y selecciona **Allow** si estás de acuerdo.
6. Cuando se cree la PR, pídele que la fusione y vuelva a cambiar tu rama local a `main`:

   ```plaintext
   Merge the PR into main. Then return to main locally, and pull the latest code so we are up to date.
   ```

7. Cuando Copilot te pida permiso para realizar acciones de GitHub y comandos de shell, revisa cada solicitud antes de aceptarla.

¡Has creado y fusionado una solicitud de incorporación de cambios con ayuda de GitHub Copilot!

## Resumen y siguientes pasos

Has explorado cómo Copilot usa las instrucciones del proyecto y has usado Copilot Chat en VS Code para:

- enviar un prompt de generación de código y observar el resultado con las instrucciones existentes;
- añadir un estándar general al archivo `.github/copilot-instructions.md`;
- volver a ejecutar el prompt y observar cómo el código propuesto aplica el nuevo estándar;
- confirmar las instrucciones y el helper de editoriales en `main` para que el siguiente ejercicio pueda usarlos.

A continuación, pondrás esas instrucciones en práctica en el [modo agente][next-lesson] mientras Copilot añade una funcionalidad al proyecto.

## Recursos

- [Archivos de instrucciones para personalizar GitHub Copilot][instruction-files]
- [Buenas prácticas para crear instrucciones personalizadas][instructions-best-practices]
- [Cinco consejos para escribir mejores instrucciones personalizadas para Copilot][copilot-instructions-five-tips]
- [Instrucciones personales para GitHub Copilot][personal-instructions]
- [Awesome Copilot: colección de archivos de instrucciones y otros recursos][awesome-copilot]

[previous-lesson]: ../0-prerequisites/
[next-lesson]: ../2-agent-mode/
[instruction-files]: https://code.visualstudio.com/docs/copilot/copilot-customization
[instructions-best-practices]: https://docs.github.com/enterprise-cloud@latest/copilot/using-github-copilot/coding-agent/best-practices-for-using-copilot-to-work-on-tasks#adding-custom-instructions-to-your-repository
[personal-instructions]: https://docs.github.com/copilot/customizing-copilot/adding-personal-custom-instructions-for-github-copilot
[copilot-instructions-five-tips]: https://github.blog/ai-and-ml/github-copilot/5-tips-for-writing-better-custom-instructions-for-copilot/
