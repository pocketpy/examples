import EditorWorker from 'url:monaco-editor/esm/vs/editor/editor.worker.js';
import * as monaco from 'monaco-editor/esm/vs/editor/editor.main.js';
import DATA from './data.js';

self.MonacoEnvironment = {
	getWorkerUrl: function (moduleId, label) {
		return EditorWorker;
	}
};

const monacoEditor = monaco.editor.create(document.getElementById('editor'), {
	value: "#include <iostream>\nusing namespace std;\n\nint main() {\n    cout << \"Hello, World!\" << endl;\n    return 0;\n}",
	language: 'cpp',
    minimap: { enabled: false }
});

const monacoInput = monaco.editor.create(document.getElementById('input'), {
	value: "",
    language: 'python',
    minimap: { enabled: false },
    folding: false,
});

const monacoOutput = monaco.editor.create(document.getElementById('output'), {
	value: "",
    language: 'plaintext',
    minimap: { enabled: false },
    readOnly: true,
    folding: false,
});

// ui bind
function selectExample(i){
    monacoEditor.setValue(DATA[i][1].source);
    monacoInput.setValue(DATA[i][1].input);
}

const select = document.getElementById('examples');
for (let i = 0; i < DATA.length; i++) {
    const option = document.createElement('option');
    option.value = i;
    option.text = DATA[i][0];
    select.appendChild(option);
}

select.onchange = function () {
    selectExample(select.selectedIndex);
}

selectExample(0);

const endpoint = 'https://pkpy-facompiler-umuvjmhvta.cn-hongkong.fcapp.run/invoke';

const runButton = document.getElementById('run');
runButton.onclick = function () {
    runButton.disabled = true;
    const source = monacoEditor.getValue();
    const input = monacoInput.getValue();

    fetch(endpoint, {
        method: 'POST',
        body: JSON.stringify({ "source": source, "input": input }),
        headers: {'Content-Type': 'application/json'}
    }).then(res => {
        if(res.status == 200) return res.json();
        alert("Failed to run code: " + res.status.toString() + " " + res.statusText);
    }).then(data => {
        monacoOutput.setValue(data.stdout + data.stderr);
        document.getElementById("outputH").textContent = "Output (" + data.elapsed_time.toFixed(2) + " s)";
        runButton.disabled = false;
    })
}
