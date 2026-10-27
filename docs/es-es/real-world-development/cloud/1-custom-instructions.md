---
title: "Ejercicio 1 - Instrucciones personalizadas (agente en la nube)"
authors:
  - geektrainer
lastUpdated: 2026-06-30
---

[← Lección anterior: Requisitos previos][previous-lesson] · [Siguiente lección: Agente en la nube de Copilot →][next-lesson]

El contexto es clave cuando se trabaja con IA generativa. Si una tarea debe realizarse de una forma concreta o Copilot necesita información de fondo, debes asegurarte de que pueda acceder a ese contexto. Los [archivos de instrucciones][instruction-files] proporcionan directrices para que Copilot entienda no solo *qué* quieres, sino también *cómo* quieres que lo haga.

En este ejercicio:

- explorarás cómo llegan a Copilot el contexto del proyecto, las directrices de desarrollo y los estándares de documentación mediante las instrucciones personalizadas del repositorio y los archivos con ámbito de ruta;
- añadirás un estándar general al archivo `.github/copilot-instructions.md`.

> [!NOTE]
> A diferencia de los recorridos de VS Code y CLI, aquí no compararás el resultado de un prompt antes y después de actualizar las instrucciones. El agente en la nube trabaja de forma asíncrona en incidencias de GitHub, por lo que es más difícil mostrar el efecto en tiempo real. Verás la influencia de las instrucciones al revisar las PR que genere más adelante.

## Archivos de instrucciones

### Escenario

Tailspin Toys tiene directrices para sus prácticas de desarrollo:

- La capa de datos siempre necesita pruebas unitarias.
- La interfaz debe estar en modo oscuro y tener un aspecto moderno.
- El código debe incluir comentarios de documentación TSDoc.
- Cada archivo debe empezar con un bloque de comentarios que describa su función.

Usarás archivos de instrucciones para proporcionar a Copilot la información necesaria para seguir estas prácticas.

### Instrucciones personalizadas

Las instrucciones personalizadas proporcionan a Copilot contexto y preferencias para que entienda mejor tu estilo y requisitos. Puedes especificar convenciones, bibliotecas y comentarios. Puedes crear instrucciones para todo el repositorio o para tipos concretos de archivos y tareas.

Hay dos tipos:

- `.github/copilot-instructions.md`, un único archivo que se envía a Copilot en **todas** las solicitudes del repositorio. Debe incluir información general del proyecto relevante para la mayoría de las solicitudes de chat o CLI, como la pila tecnológica, una descripción del proyecto, buenas prácticas y directrices globales.
- `.github/instructions/*.instructions.md`, archivos con instrucciones para tareas o tipos de archivo concretos, como TypeScript, Astro, componentes de interfaz o pruebas unitarias.

> [!NOTE]
> En el IDE, los archivos de instrucciones solo se usan para generar código en Copilot Chat, no para completar código ni para sugerir la siguiente edición.
>
> Copilot Chat, Copilot CLI y Copilot cloud agent usan las instrucciones del repositorio y los archivos `*.instructions.md` con frontmatter `applyTo`.
>
> Copilot también [admite otros formatos de instrucciones][custom-instructions-support], como AGENTS.md y CLAUDE.md.

### Buenas prácticas para gestionar archivos de instrucciones

El proyecto de ejemplo muestra un enfoque posible:

- Mantén `copilot-instructions.md` centrado en el proyecto: su descripción, estructura y estándares globales.
- Usa `*.instructions.md` para tipos de archivo (pruebas unitarias, componentes Astro, capa de datos) o tareas concretas.
- Escribe en lenguaje natural, con directrices claras y ejemplos de código correctos e incorrectos.

No existe una única forma de crear archivos de instrucciones ni de usar IA. La experimentación te ayudará a encontrar la solución adecuada para tu proyecto.

> [!TIP]
> Los proyectos con GitHub Copilot deberían disponer de una colección completa de archivos de instrucciones. En este proyecto encontrarás archivos para varios tipos de tareas, incluidas las [actualizaciones de interfaz][ui-instructions] y [Astro][astro-instructions].
>
> Copilot también puede generar archivos de instrucciones. Cada entorno ofrece esta opción de forma diferente (por ejemplo, **Configure Chat → Generate Agent Instructions** en VS Code o `/init` en Copilot CLI). La lección correspondiente indicará cuándo usarla.
>
> Para buscar plantillas o ideas, explora [awesome-copilot][awesome-copilot], un repositorio de instrucciones, agentes personalizados y otros recursos.

[ui-instructions]: https://github.com/github-samples/tailspin-toys/blob/main/.github/instructions/ui.instructions.md
[astro-instructions]: https://github.com/github-samples/tailspin-toys/blob/main/.github/instructions/astro.instructions.md
[awesome-copilot]: https://github.com/github/awesome-copilot
[custom-instructions-support]: https://docs.github.com/copilot/reference/custom-instructions-support

## Explorar los archivos de instrucciones del proyecto

Lee los archivos incluidos en el repositorio: `.github/copilot-instructions.md` y los distintos `*.instructions.md`. Ábrelos en la interfaz web de GitHub o en un codespace.

1. Abre `.github/copilot-instructions.md`.
2. Explora la descripción del proyecto y las secciones **Agent notes**, **Code standards**, **Scripts** y **Repository Structure**. En **Code standards**, observa las directrices anidadas para **GitHub Actions Workflows**; se aplican a cualquier interacción con Copilot.
3. Explora `.github/instructions`. Hay instrucciones para Astro, la capa de datos Drizzle, pruebas y otros ámbitos.
4. Abre `.github/instructions/unit-tests.instructions.md`. El campo `applyTo` del principio define un patrón relativo a la raíz del repositorio; por ejemplo, los archivos TypeScript de pruebas que coincidan con `**/*.test.ts`.
5. Observa las instrucciones para crear pruebas unitarias.
6. Abre `.github/instructions/drizzle.instructions.md` y ve al final. Observa los enlaces a otros archivos, como `unit-tests.instructions.md`, y a archivos existentes. Las rutas son relativas al archivo de instrucciones.

> [!NOTE]
> La sección **Code formatting requirements** de `copilot-instructions.md` describe los estándares del proyecto, pero todavía no exige documentación en el código. A continuación añadirás directrices sobre los comentarios TSDoc y los encabezados de comentario.

## Añadir un estándar para todo el repositorio

En este ejercicio harás un único cambio: añadirás una regla general para que la documentación se incluya en el código mediante comentarios TSDoc y un encabezado de comentario para cada archivo. El agente en la nube la aplicará a las incidencias que le asignes más adelante.

Antes, prepara una rama. El agente leerá las instrucciones de la rama a la que apunte la incidencia, pero confirmarás los cambios por separado:

1. En el terminal del codespace, crea una rama nueva y cámbiate a ella:

   ```bash
   git checkout -b custom-instructions-cloud
   ```

El archivo `.github/copilot-instructions.md` proporciona información general del proyecto. Añade el estándar:

1. Vuelve a abrir `.github/copilot-instructions.md`.
2. Localiza **Code formatting requirements**, cerca de la línea 27. Todavía no hay una regla para documentar el código.
3. Añade estas líneas de Markdown debajo de los estándares existentes:

   ```markdown
   - Every exported function should have a TSDoc comment describing its purpose, parameters, and return value.
   - Before imports or any code, add a comment block to the file that explains its purpose.
   ```

4. Guarda `copilot-instructions.md`.

> [!TIP]
> Como has visto en la lección anterior, las instrucciones generales van en `.github/copilot-instructions.md`; las específicas para lenguajes, tipos de archivo o tareas van en `*.instructions.md`. El archivo general es adecuado para estándares como los comentarios de documentación.

## Confirmar, enviar y fusionar la actualización de instrucciones

El agente en la nube lee las instrucciones de la rama a la que apunta la incidencia. En el siguiente ejercicio, la rama de trabajo del agente partirá de `main`, así que debes incorporar allí las instrucciones para que las pueda usar.

1. Prepara y confirma el cambio:

   ```bash
   git add .github/copilot-instructions.md
   git commit -m "Add doc comment and file-header standards to copilot instructions"
   ```

2. Envía la rama:

   ```bash
   git push -u origin custom-instructions-cloud
   ```

3. En github.com, abre una solicitud de incorporación de cambios de `custom-instructions-cloud` a `main` y fusiónala. El agente leerá estas instrucciones cuando trabaje en incidencias asignadas en el siguiente ejercicio.

> [!TIP]
> Si prefieres trabajar directamente en `main` durante el taller, puedes omitir la rama y confirmar el cambio directamente en `main`. La rama permite practicar un flujo de trabajo habitual en proyectos reales.

## Resumen y siguientes pasos

Has explorado cómo usa Copilot las instrucciones del proyecto y has añadido un estándar general a `.github/copilot-instructions.md`. Verás cómo se aplica en las PR que genere el agente en la nube.

A continuación, [asignarás tu primera incidencia al agente en la nube de Copilot][next-lesson].

## Recursos

- [Archivos de instrucciones para personalizar GitHub Copilot][instruction-files]
- [Buenas prácticas para crear instrucciones personalizadas][instructions-best-practices]
- [Cinco consejos para escribir mejores instrucciones personalizadas para Copilot][copilot-instructions-five-tips]
- [Awesome Copilot: colección de archivos de instrucciones y otros recursos][awesome-copilot]

[previous-lesson]: ../0-prerequisites/
[next-lesson]: ../2-cloud-agent/
[instruction-files]: https://docs.github.com/copilot/customizing-copilot/about-customizing-github-copilot-chat-responses
[instructions-best-practices]: https://docs.github.com/enterprise-cloud@latest/copilot/using-github-copilot/coding-agent/best-practices-for-using-copilot-to-work-on-tasks#adding-custom-instructions-to-your-repository
[copilot-instructions-five-tips]: https://github.blog/ai-and-ml/github-copilot/5-tips-for-writing-better-custom-instructions-for-copilot/
