-- Co-stars with Kevin Bacon
SELECT DISTINCT p.name AS CoStars FROM people AS p
JOIN stars AS s ON p.id = s.person_id
WHERE NOT p.name = "Kevin Bacon" AND s.movie_id IN
(SELECT stars.movie_id FROM stars 
JOIN people ON stars.person_id = people.id
WHERE people.name = "Kevin Bacon" AND people.birth = 1958);