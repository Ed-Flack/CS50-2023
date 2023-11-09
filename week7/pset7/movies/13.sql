SELECT name FROM people, stars, movies
WHERE person_id = people.id
AND movies.id = movie_id
AND people.id != (SELECT people.id from people WHERE name = 'Kevin Bacon' AND birth = 1958)
AND movies.id IN (SELECT movies.id from movies, stars, people
    WHERE movies.id = movie_id
    AND person_id = people.id
    AND name = 'Kevin Bacon'
    AND birth = 1958);
