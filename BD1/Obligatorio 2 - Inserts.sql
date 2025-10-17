USE OBLIGATORIOBD1;

-- ==============================================
-- TABLE: AUTORES
-- ==============================================
INSERT INTO
    AUTORES (NOM_AUTOR, NOTAS)
VALUES (
        'Gabriel García Márquez',
        'Autor colombiano de realismo mágico.'
    ),
    (
        'Jorge Luis Borges',
        'Escritor argentino, poeta y ensayista.'
    ),
    (
        'Isabel Allende',
        'Autora chilena reconocida internacionalmente.'
    ),
    (
        'Oscar Bierre',
        'Novelista peruano, Premio Nobel.'
    ),
    (
        'Julio Cortázar',
        'Autor argentino de narrativa fantástica.'
    ),
    (
        'Pablo Neruda',
        'Poeta chileno, Premio Nobel de Literatura.'
    ),
    (
        'Miguel de Cervantes',
        'Autor de Don Quijote de la Mancha.'
    ),
    (
        'Reina Inglesa',
        'Novelista inglesa de la Regencia.'
    ),
    (
        'Charles Dickens',
        'Escritor inglés de la era victoriana.'
    ),
    (
        'Ernest Hemingway',
        'Autor estadounidense, Premio Nobel.'
    ),
    (
        'Harry Potter',
        'Autor estadounidense de Tom Sawyer.'
    ),
    (
        'Haruki Murakami',
        'Novelista japonés contemporáneo.'
    ),
    (
        'Fyodor Dostoyevsky',
        'Novelista ruso, autor de Crimen y Castigo.'
    ),
    (
        'Leo Tolstoy',
        'Autor ruso de Guerra y Paz.'
    ),
    (
        'Eduardo Mendoza',
        'Novelista español, conocido por "La ciudad de los prodigios".'
    ),
    (
        'Gabriela Cañas',
        'Autora de Literatura contemporánea.'
    );

-- ==============================================
-- TABLE: EDITORIALES
-- ==============================================
INSERT INTO
    EDITORIALES (COD_EDITORIAL, NOM_EDITORIAL)
VALUES (3001, 'Penguin Random House'),
    (3942, 'HarperCollins'),
    (3245, 'Planeta'),
    (3390, 'Alfaguara'),
    (3525, 'Anagrama'),
    (3666, 'Seix Barral'),
    (3799, 'Debolsillo'),
    (4077, 'Vintage Books'),
    (
        7077,
        'Oxford University Press'
    ),
    (
        7230,
        'Cambridge University Press'
    ),
    (7377, 'Tusquets'),
    (7510, 'Emece'),
    (
        7699,
        'Editorial Sudamericana'
    ),
    (
        7822,
        'Fondo de Cultura Económica'
    ),
    (7988, 'Editorial Norma');

-- ==============================================
-- TABLE: TEMAS
-- ==============================================
INSERT INTO
    TEMAS (TEMA)
VALUES ('Realismo mágico'),
    ('Poesía'),
    ('Fantasía'),
    ('Drama'),
    ('Romance'),
    ('Aventura'),
    ('Filosofía'),
    ('Historia'),
    ('Ciencia ficción'),
    ('Ensayo'),
    ('Psicología'),
    ('Sociedad'),
    ('Cuento corto'),
    ('Agricultura'),
    ('Misterio'),
    ('Literatura');
-- Added 'Literatura' for queries

-- ==============================================
-- TABLE: FUNCIONES
-- ==============================================
INSERT INTO
    FUNCIONES (FUNCION)
VALUES ('Autor principal'),
    ('Coautor'),
    ('Traductor'),
    ('Editor'),
    ('Revisor'),
    ('Compilador'),
    ('Prólogo'),
    ('Epílogo'),
    ('Corrector'),
    ('Ilustrador'),
    ('Adaptador'),
    ('Guionista'),
    ('Colaborador'),
    ('Documentalista'),
    ('Investigador');

-- ==============================================
-- TABLE: OBRAS
-- ==============================================
INSERT INTO
    OBRAS (
        COD_OBRA,
        TITULO,
        UBICACION,
        EDICION,
        PAIS,
        PAGINAS,
        ISBN
    )
VALUES (
        7512,
        'Cien años de soledad',
        'A1',
        '1ra',
        'Colombia',
        471,
        '9780307474728'
    ),
    (
        3521,
        'El Aleph',
        'A2',
        '2da',
        'Argentina',
        189,
        '9788497594253'
    ),
    (
        1531,
        'La casa de los espíritus',
        'A3',
        '1ra',
        'Chile',
        433,
        '9788408053641'
    ),
    (
        2513,
        'La ciudad y los perros',
        'A4',
        '3ra',
        'Perú',
        351,
        '9788439724601'
    ),
    (
        5541,
        'Rayuela',
        'A5',
        '1ra',
        'Argentina',
        500,
        '9788437604943'
    ),
    (
        8514,
        'Veinte poemas de amor',
        'B1',
        '5ta',
        'Chile',
        120,
        '9788497594239'
    ),
    (
        7527,
        'Don Quijote de la Mancha',
        'B2',
        '4ta',
        'España',
        863,
        '9788420412142'
    ),
    (
        1015,
        'Orgullo y prejuicio',
        'B3',
        '6ta',
        'Reino Unido',
        279,
        '9788491051806'
    ),
    (
        1161,
        'Oliver Twist',
        'B4',
        '2da',
        'Reino Unido',
        368,
        '9788491052759'
    ),
    (
        1216,
        'El viejo y el mar',
        'B5',
        '3ra',
        'EE.UU.',
        127,
        '9788497594253'
    ),
    (
        4371,
        'Las aventuras de Tom Sawyer',
        'C1',
        '2da',
        'EE.UU.',
        250,
        '9788491054722'
    ),
    (
        3477,
        'Tokio Blues',
        'C2',
        '1ra',
        'Japón',
        382,
        '9788499082475'
    ),
    (
        5556,
        'Crimen y castigo',
        'C3',
        '1ra',
        'Rusia',
        671,
        '9780140449136'
    ),
    (
        6745,
        'Guerra y paz',
        'C4',
        '1ra',
        'Rusia',
        1225,
        '9788491051684'
    ),
    (
        8788,
        'La metamorfosis',
        'C5',
        '1ra',
        'Chequia',
        201,
        '9788491052018'
    );

-- ==============================================
-- TABLE: INVENTARIO
-- ==============================================
INSERT INTO
    INVENTARIO (
        COD_OBRA,
        FORMA_INGRESO,
        FECHA_RECEPCION
    )
VALUES (7512, 'Compra', '2023-01-10'),
    (
        3521,
        'Donación',
        '2023-02-05'
    ),
    (1531, 'Compra', '2023-03-15'),
    (
        2513,
        'Intercambio',
        '2023-03-20'
    ),
    (5541, 'Compra', '2023-04-01'),
    (
        8514,
        'Donación',
        '2023-05-10'
    ),
    (7527, 'Compra', '2023-06-22'),
    (
        1015,
        'Donación',
        '2023-07-13'
    ),
    (1161, 'Compra', '2023-08-18'),
    (
        1216,
        'Intercambio',
        '2023-09-25'
    ),
    (4371, 'Compra', '2023-10-02'),
    (3477, 'Compra', '2023-10-15'),
    (
        5556,
        'Donación',
        '2023-11-07'
    ),
    (6745, 'Compra', '2023-12-11'),
    (8788, 'Compra', '2024-01-09');

-- ==============================================
-- TABLE: OBRA_AUTOR
-- ==============================================
INSERT INTO
    OBRA_AUTOR (
        COD_OBRA,
        COD_AUTOR,
        COD_FUNCION
    )
VALUES (7512, 1, 1),
    (3521, 2, 2),
    (1531, 3, 3),
    (2513, 4, 4),
    (5541, 5, 5),
    (8514, 6, 1),
    (7527, 7, 1),
    (1015, 2, 3),
    (1161, 2, 3),
    (1216, 3, 7),
    (4371, 3, 7),
    (3477, 8, 8),
    (5556, 9, 5),
    (6745, 5, 6),
    (8788, 10, 6),
    (1531, 16, 1);
-- Gabriela Cañas

-- ==============================================
-- TABLE: OBRA_EDITORIAL
-- ==============================================
INSERT INTO
    OBRA_EDITORIAL (COD_OBRA, COD_EDITORIAL)
VALUES (7512, 3001),
    (3521, 3245),
    (1531, 7077),
    (2513, 3390),
    (5541, 7230),
    (8514, 3525),
    (7527, 7377),
    (1015, 3666),
    (1161, 7510),
    (1216, 3799),
    (4371, 7699),
    (3477, 3942),
    (5556, 7822),
    (6745, 4077),
    (8788, 7988);

-- ==============================================
-- TABLE: OBRA_TEMA
-- ==============================================
INSERT INTO
    OBRA_TEMA (COD_OBRA, COD_TEMA)
VALUES (7512, 16), -- Literatura
    (3521, 13),
    (1531, 16), -- Literatura
    (2513, 4),
    (5541, 7),
    (8514, 2),
    (7527, 6),
    (1015, 7),
    (1161, 12),
    (1216, 7),
    (4371, 7),
    (3477, 7),
    (5556, 11),
    (6745, 14),
    (8788, 15);