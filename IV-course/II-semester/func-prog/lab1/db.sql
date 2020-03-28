CREATE TABLE lab1_teacher
(
    id      SERIAL PRIMARY KEY,
    name    VARCHAR(20) NOT NULL,
    surname VARCHAR(20) NOT NULL
);


CREATE TABLE lab1_section
(
    id        SERIAL PRIMARY KEY,
    name      VARCHAR(20) NOT NULL,
    teacherID INT REFERENCES lab1_teacher (id)
);

CREATE TABLE lab1_student
(
    id        SERIAL PRIMARY KEY,
    name      VARCHAR(20) NOT NULL,
    surname   VARCHAR(20) NOT NULL,
    sectionId INT REFERENCES lab1_section (id)
);


CREATE TABLE lab1_schedule
(
    id        SERIAL PRIMARY KEY,
    sectionID INT REFERENCES lab1_section (id) NOT NULL,
    beginDay  VARCHAR(3)                       NOT NULL,
    beginTime TIME                             NOT NULL,
    endTime   TIME                             NOT NULL
);

CREATE TABLE lab1_competitive
(
    id        SERIAL PRIMARY KEY,
    sectionID SERIAL REFERENCES lab1_section (id) NOT NULL,
    begin_    TIMESTAMP                           NOT NULL,
    end_      TIMESTAMP                           NOT NULL,
    winner    INT REFERENCES lab1_student (id)
);

INSERT INTO lab1_teacher
        (name, surname)
VALUES  ('Mourinho', 'Fizruk'),
        ('Michael', 'Felps'),
        ('Cobie', 'Bryant');

INSERT INTO lab1_section
        (name, teacherID)
VALUES  ('Football', 1),
        ('Swimming', 2),
        ('Basketball', 3);

INSERT INTO lab1_student
        (name, surname, sectionId)
VALUES  ('A', 'B', 1),
        ('C', 'Bb', 1),
        ('D', 'Ba', 2),
        ('E', 'Bf', 2),
        ('G', 'Baf', 3),
        ('H', 'Buff', 2),
        ('Heh', 'Butt', 3),
        ('F', 'Back', 1);

INSERT INTO lab1_schedule
        (sectionID, beginDay, beginTime, endTime)
VALUES  (1, 'Mon', '16:00', '18:00'),
        (1, 'Trd', '16:00', '18:00'),
        (2, 'Wed', '16:00', '18:00'),
        (2, 'Frd', '17:00', '19:00'),
        (3, 'Tue', '18:00', '21:00'),
        (3, 'Sun', '19:00', '21:00');

INSERT INTO lab1_competitive
        (sectionID, begin_, end_)
VALUES  (1, '2016-11-04 14:00:00', '2016-11-04 20:00:00'),
        (1, '2016-11-05 16:00:00', '2016-11-04 20:00:00'),
        (1, '2016-11-07 12:00:00', '2016-11-04 20:00:00');