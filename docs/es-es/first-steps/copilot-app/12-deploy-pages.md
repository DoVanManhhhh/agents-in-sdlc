---
title: "Lección 12 - Publicar el sitio con GitHub Pages"
description: "Usa la aplicación GitHub Copilot para configurar un flujo de trabajo de Pages, revisar su solicitud de incorporación de cambios y comprobar que Space Quiz está disponible."
authors:
  - jamesmontemagno
lastUpdated: 2026-10-12
---

Publica Space Quiz en GitHub Pages para que todo el mundo pueda acceder a él. Copilot puede preparar el flujo de trabajo y guiarte durante la publicación, pero debes revisar los cambios y confirmar que el sitio está disponible.

En esta lección:

- pedirás a Copilot que configure una publicación en GitHub Pages;
- revisarás el flujo de trabajo y la solicitud de incorporación de cambios antes de fusionarla;
- seguirás la publicación y comprobarás el sitio publicado.

## Escenario

Space Quiz ya está en un repositorio de GitHub, pero hace falta una forma sencilla de probarlo. Publicar este sitio de un solo archivo con GitHub Pages lo hace accesible mediante una URL pública sin añadir un servidor ni dependencias de ejecución.

## Pedir a Copilot que publique el sitio

En la sesión de la aplicación Copilot para `space-quiz`, envía este prompt:

```plaintext
Enable GitHub Pages for this repository. Create a GitHub Actions workflow that builds the website if needed and deploys it to GitHub Pages. Add a README describing the app and how to run it locally if one does not already exist. Create a pull request with these changes and merge it after required checks pass. Monitor the deployment until it succeeds, then report the final URL of the live website. If you lack permission to enable Pages or merge, tell me exactly what I need to approve or do; do not report success until the site is live.
```

![Diagrama de tres fases: una solicitud de incorporación de cambios de space-quiz fusionada; una ejecución correcta de Deploy website en GitHub Actions con los pasos Build website, Upload artifact y Deploy to Pages; y Space Quiz disponible en yourname.github.io/space-quiz/.](../../../_images/first-steps-app-pages-deploy.svg)

> [!WARNING]
> Este prompt pide al agente que cree y fusione una solicitud de incorporación de cambios y cambie la configuración de Pages del repositorio. Revisa las diferencias, los permisos de publicación y las solicitudes de aprobación de GitHub antes de continuar.

## Revisar el flujo de trabajo y comprobar la publicación

1. Confirma que el archivo README solo se añade si el repositorio todavía no tiene uno.
2. Revisa los cambios de la solicitud de incorporación de cambios, incluidos los pasos de compilación y publicación del flujo de trabajo.
3. Fusiónala solo cuando se hayan superado las comprobaciones obligatorias.
4. Sigue la ejecución de publicación de GitHub Actions hasta que termine correctamente.
5. Abre la URL indicada y confirma que Space Quiz se carga.

Si el agente no puede habilitar Pages o fusionar la solicitud, sigue las instrucciones concretas que te proporcione. No des la tarea por terminada hasta que la publicación haya finalizado correctamente y el sitio esté disponible.

## Resumen y siguientes pasos

Space Quiz ya está disponible como sitio publicado y has comprobado la publicación en lugar de confiar únicamente en el informe del agente. Continúa con la [Lección 13: Revisión y siguientes pasos][next-lesson].

[next-lesson]: ../13-review/
