USE OBLIGATORIOBD1;

-- ==============================================
-- TABLE: AUTORES
-- ==============================================
CREATE TABLE AUTORES (
    COD_AUTOR INT PRIMARY KEY AUTO_INCREMENT,
    NOM_AUTOR VARCHAR(100) NOT NULL,
    NOTAS TEXT
);

-- ==============================================
-- TABLE: EDITORIALES
-- ==============================================
CREATE TABLE EDITORIALES (
    COD_EDITORIAL INT PRIMARY KEY,
    NOM_EDITORIAL VARCHAR(100) NOT NULL
);

-- ==============================================
-- TABLE: TEMAS
-- ==============================================
CREATE TABLE TEMAS (
    COD_TEMA INT PRIMARY KEY AUTO_INCREMENT,
    TEMA VARCHAR(100) NOT NULL
);

-- ==============================================
-- TABLE: FUNCIONES
-- ==============================================
CREATE TABLE FUNCIONES (
    COD_FUNCION INT PRIMARY KEY AUTO_INCREMENT,
    FUNCION VARCHAR(100) NOT NULL
);

-- ==============================================
-- TABLE: OBRAS
-- ==============================================
CREATE TABLE OBRAS (
    COD_OBRA INT PRIMARY KEY,
    TITULO VARCHAR(200) NOT NULL,
    UBICACION VARCHAR(100),
    EDICION VARCHAR(50),
    PAIS VARCHAR(50),
    PAGINAS INT,
    ISBN VARCHAR(20)
);

-- ==============================================
-- TABLE: INVENTARIO
-- ==============================================
CREATE TABLE INVENTARIO (
    COD_REGISTRO INT PRIMARY KEY AUTO_INCREMENT,
    COD_OBRA INT NOT NULL,
    FORMA_INGRESO VARCHAR(100),
    FECHA_RECEPCION DATE,
    FOREIGN KEY (COD_OBRA) REFERENCES OBRAS (COD_OBRA) ON DELETE CASCADE ON UPDATE CASCADE
);

-- ==============================================
-- TABLE: OBRA_AUTOR
-- ==============================================
CREATE TABLE OBRA_AUTOR (
    COD_OBRA INT NOT NULL,
    COD_AUTOR INT NOT NULL,
    COD_FUNCION INT NOT NULL,
    PRIMARY KEY (
        COD_OBRA,
        COD_AUTOR,
        COD_FUNCION
    ),
    FOREIGN KEY (COD_OBRA) REFERENCES OBRAS (COD_OBRA) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (COD_AUTOR) REFERENCES AUTORES (COD_AUTOR) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (COD_FUNCION) REFERENCES FUNCIONES (COD_FUNCION) ON DELETE CASCADE ON UPDATE CASCADE
);

-- ==============================================
-- TABLE: OBRA_EDITORIAL
-- ==============================================
CREATE TABLE OBRA_EDITORIAL (
    COD_OBRA INT NOT NULL,
    COD_EDITORIAL INT NOT NULL,
    PRIMARY KEY (COD_OBRA, COD_EDITORIAL),
    FOREIGN KEY (COD_OBRA) REFERENCES OBRAS (COD_OBRA) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (COD_EDITORIAL) REFERENCES EDITORIALES (COD_EDITORIAL) ON DELETE CASCADE ON UPDATE CASCADE
);

-- ==============================================
-- TABLE: OBRA_TEMA
-- ==============================================
CREATE TABLE OBRA_TEMA (
    COD_OBRA INT NOT NULL,
    COD_TEMA INT NOT NULL,
    PRIMARY KEY (COD_OBRA, COD_TEMA),
    FOREIGN KEY (COD_OBRA) REFERENCES OBRAS (COD_OBRA) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (COD_TEMA) REFERENCES TEMAS (COD_TEMA) ON DELETE CASCADE ON UPDATE CASCADE
);