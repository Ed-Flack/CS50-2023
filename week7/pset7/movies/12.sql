SELECT title FROM people, stars, movies
WHERE people.id = person_id
AND movie_id = movies.id
AND name = 'Jennifer Lawrence'
AND movies.id IN (SELECT movies.id FROM people, stars, movies
    WHERE people.id = person_id
    AND movie_id = movies.id
    AND name = 'Bradley Cooper');
