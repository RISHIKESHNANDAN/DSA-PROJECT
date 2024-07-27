document.getElementById('goalForm').addEventListener('submit', function (e) {
    e.preventDefault();

    const title = document.getElementById('title').value;
    const description = document.getElementById('description').value;
    const deadline = document.getElementById('deadline').value;
    const priority = document.getElementById('priority').value;

    const goal = { title, description, deadline, priority };

    addGoalToList(goal);
    saveGoal(goal);

    document.getElementById('goalForm').reset();
});

function addGoalToList(goal) {
    const goalList = document.getElementById('goalList');
    const goalDiv = document.createElement('div');
    goalDiv.classList.add('goal');
    goalDiv.innerHTML = `
        <h3>${goal.title}</h3>
        <p>${goal.description}</p>
        <p>Deadline: ${goal.deadline}</p>
        <p>Priority: ${goal.priority}</p>
        <div class="actions">
            <button onclick="removeGoal('${goal.title}')">Remove</button>
        </div>
    `;
    goalList.appendChild(goalDiv);
}

function saveGoal(goal) {
    let goals = JSON.parse(localStorage.getItem('goals')) || [];
    goals.push(goal);
    localStorage.setItem('goals', JSON.stringify(goals));
}

function removeGoal(title) {
    let goals = JSON.parse(localStorage.getItem('goals')) || [];
    goals = goals.filter(goal => goal.title !== title);
    localStorage.setItem('goals', JSON.stringify(goals));
    displayGoals();
}

function displayGoals() {
    const goalList = document.getElementById('goalList');
    goalList.innerHTML = '';
    const goals = JSON.parse(localStorage.getItem('goals')) || [];
    goals.forEach(goal => addGoalToList(goal));
}

document.addEventListener('DOMContentLoaded', displayGoals);
