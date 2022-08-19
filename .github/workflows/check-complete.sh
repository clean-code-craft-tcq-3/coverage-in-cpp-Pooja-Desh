#!/bin/bash
set -e

if grep -q _enter *.md; then
  echo "Replace all text having (cyclomatic complexity can be surely reduced with this approach in my working project) with your input"
  exit 1
fi
