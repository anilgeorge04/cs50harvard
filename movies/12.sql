-- Movies starring Johnny Depp and Helena Bonham Carter
SELECT m.title FROM movies AS m
JOIN stars AS s ON m.id = s.movie_id
JOIN people AS p ON s.person_id = p.id
WHERE p.name = 'Johnny Depp' AND s.movie_id IN
(SELECT movie_id FROM stars JOIN people ON stars.person_id=people.id
WHERE people.name = 'Helena Bonham Carter');