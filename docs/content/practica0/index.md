+++
date = '2026-02-20T23:10:01-08:00'
draft = false
title = 'Practica 0: Manejo de Repositorios'
+++

## Sesión 1: Markdown (El lenguaje de los devs)

### Descripción
Markdown es un lenguaje de marcado súper ligero. Básicamente, es escribir texto plano que se ve genial sin tener que pelearse con los menús de Word. Es el estándar para documentar cualquier proyecto en GitHub.

### Desarrollo
* **¿Cómo se usa?** Solo creas un archivo con extensión `.md` y usas símbolos simples para dar formato.
* **Sintaxis que salva vidas:**
    * `#` para títulos (como este).
    * `**Negrita**` para resaltar lo importante.
    * `*` para hacer listas de tareas.
    * `[Texto](URL)` para meter links a recursos.
    * Bloques de código con tres tildes invertidas (\` \` \`) para que el código se vea limpio.

---

## Sesión 2: Git y GitHub

### Descripción
**Git** es la herramienta que lleva el historial de todo lo que haces (tu máquina del tiempo), y **GitHub** es la red social/nube donde guardas esos proyectos para que el mundo los vea (y no se pierdan si explota tu PC).



### Desarrollo
Para subir mi información a la nube, los pasos que sigo siempre son:
1.  **Inicializar:** `git init` (solo la primera vez).
2.  **Preparar:** `git add .` (le digo a Git: "mira estos cambios").
3.  **Confirmar:** `git commit -m "un mensaje claro"` (tomo la foto del momento).
4.  **Subir:** `git push origin main` (mando todo a mi repo en GitHub).

---

## Sesión 3: Magia con Hugo y GitHub Actions

### Descripción
Aquí es donde todo se conecta. **Hugo** es un generador de sitios estáticos (SSG) que vuela de rápido. **GitHub Actions** es un robot que automatiza tareas: cada vez que subo algo, el robot lo publica solo.

### Desarrollo
* **Crear el sitio:** Usé `hugo new site` y le puse un tema para que se vea profesional.
* **Automatización (CI/CD):** Configuré un archivo `.yaml` en la carpeta de Workflows. Este archivo le dice a GitHub: *"Oye, cada vez que haga un push, construye el sitio de Hugo y súbelo a mi GitHub Pages"*.
* **El resultado:** Una página web real, hosteada gratis y que se actualiza solita.

---

## Mis Enlaces
* **Mi Portafolio en GitHub:** [https://github.com/kmeza1402/portafolio_PP]
* **Mi Página en Vivo:** [(http://localhost:1313/practica0/)]

---

## Conclusión
La combinación de estas herramientas establece un flujo de trabajo profesional. El dominio de la terminal y Git no solo facilita la gestión de archivos, sino que permite la implementación de metodologías de Despliegue Continuo.

---
