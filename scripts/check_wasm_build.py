#!/usr/bin/env python3
"""Check that the WebAssembly build of the game starts in a browser.

Usage: python3 check_wasm_build.py FOLDER

FOLDER must contain the 'index.html' of the WebAssembly build.
Opens the game in headless Chrome, takes a screenshot of the menu,
presses 'S' to start a game and takes a screenshot of the maze.
Fails if the page has errors or if the screenshots show nothing.
"""
import functools
import http.server
import io
import sys
import threading

from PIL import Image
from playwright.sync_api import sync_playwright

folder = sys.argv[1]
handler = functools.partial(http.server.SimpleHTTPRequestHandler, directory=folder)
server = http.server.ThreadingHTTPServer(("127.0.0.1", 8123), handler)
threading.Thread(target=server.serve_forever, daemon=True).start()

problems = []


def n_colors(png_bytes):
    """Count the number of different colors in a screenshot."""
    image = Image.open(io.BytesIO(png_bytes)).convert("RGB")
    return len(set(image.getdata()))


with sync_playwright() as p:
    browser = p.chromium.launch(channel="chrome", args=["--use-gl=swiftshader", "--enable-unsafe-swiftshader"])
    page = browser.new_page(viewport={"width": 800, "height": 600})
    page.on("console", lambda m: print(f"console.{m.type}: {m.text}"))
    page.on("pageerror", lambda e: problems.append(f"page error: {e}"))
    page.goto("http://127.0.0.1:8123/index.html")

    # Wait until Qt has created the canvas the game draws on
    page.wait_for_selector("canvas", state="attached", timeout=120_000)
    page.wait_for_timeout(5_000)
    menu = page.screenshot(path="menu.png")
    print(f"Menu screenshot has {n_colors(menu)} colors")
    if n_colors(menu) < 10:
        problems.append("the menu screenshot is (nearly) blank")

    # Start a game
    page.mouse.click(400, 300)
    page.keyboard.press("s")
    page.wait_for_timeout(5_000)
    maze = page.screenshot(path="maze.png")
    print(f"Maze screenshot has {n_colors(maze)} colors")
    if maze == menu:
        problems.append("pressing 'S' did not change the screen")

    browser.close()

server.shutdown()
for problem in problems:
    print(f"ERROR: {problem}")
sys.exit(1 if problems else 0)
