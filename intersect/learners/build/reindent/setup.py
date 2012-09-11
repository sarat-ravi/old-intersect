# vim:fileencoding=utf-8

import sys
from distutils.core import setup


def main():
    setup(
        name='Reindent',
        version='0.1.1',
        author="Tim Peters",
        author_email='nottimsemail@notadomain.foo',
        scripts=['reindent'],
        py_modules=['reindent'],
        maintainer="Dan Buch",
        maintainer_email="dan@meatballhat.com",
        description='reindent script by Tim Peters',
        keywords=['reindent', 'pep8', 'syntax', 'lint', 'tab', 'space'],
        classifiers=[
            "Development Status :: 6 - Mature",
            "Environment :: Console",
            "Intended Audience :: Developers",
            "License :: Public Domain",
            "Natural Language :: English",
            "Programming Language :: Python",
            "Topic :: Software Development :: Quality Assurance",
        ],
        long_description=open('README.txt').read(),
        platforms=['any'],
        license="Public Domain"
    )

    return 0


if __name__ == '__main__':
    sys.exit(main())
