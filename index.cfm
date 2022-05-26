<!--
Using header2.cfm so that img id="heroImage" is not displayed!
-->
<cfinclude template="/template2018/header2.cfm">
<style>
	#content {
		width: 100%;
		display: flex;
		justify-content: center;
		align-items: center;
		flex-direction: column;
	}
	
	.row {
		width: 100%;
		height: auto;
		display: block;
		margin-bottom: 10px;
		text-align: center;
	}
	
	#toolsDisplay {
		width: 100%;
		height: auto;
		display: flex;
		justify-content: space-around;
		align-items: flex-start;
		flex-direction: row;
		flex-wrap: wrap;
	}
	
	.tool {
		width: 330px;
		height: 350px;
		margin: 10px;
		margin-bottom: 20px;
		border-radius: 5px;
		box-shadow: rgba(0, 0, 0, 0.1) 0px 5px 5px 0px;
		transition: box-shadow 0.3s;
	}
	
	.largeTool {
		width: 450px;
	}
	
	.tool:hover {
		box-shadow: 0 10px 20px 0 rgba(0, 0, 0, 0.2);
	}
	
	.toolImage {
		width: 100%;
		height: 55%;
		border-top-left-radius: 5px;
		border-top-right-radius: 5px;
		background-attachment: scroll;
		background-size: cover;
		background-position: center center;
		background-repeat: no-repeat;
	}
	
	.toolItemLink {
		font-size: 15px;
		font-weight: bold;
		cursor: pointer;
	}
	
	.itItemLink {
		margin-bottom: 15px;
		width: 50%;
	}
	
	.itRecords {
		width: 100%;
		height: auto;
		display: flex;
		justify-content: space-between;
		align-items: flex-start;
		flex-direction: row;
		flex-wrap: wrap;
		padding: 10px;
	}
	
	@media only screen and (max-width: 767px) {
		.itRecords {
			height: auto;
		}
		.itItemLink {
			width: 100%;
		}
		.tool {
			width: 90%;
		}
	}

body,td,th {
    font-size: 10px;
}
</style>
<section id="content">
<div class="row">
	<h1><b>Chapter Leaders Toolbox</b></h1>
</div>
	
<div class="row">
	<div id="toolsDisplay">
		<cf_checkRole role="chapteradmin">
			
			<div id="chapterActivities" class="tool">
				<div class="toolImage" style="background-image:url(images/chapterreport2.jpg)">
				</div>
				<h3>Chapter Activities</h3>
				<a class="toolItemLink" href="/chapterreports" target="_self">View Chapter Reports and Planning</a>
				<br>
				<a id="requestEmailLink" class="toolItemLink" href="" target="_self">Create Event / Request Email</a>
			</div>
			
			<div id="studentTools" class="tool">
				<div class="toolImage" style="background-image:url(images/students2.jpg)">
				</div>
				<h3>Student Tools</h3>
				<a class="toolItemLink" href="/chapters/newstu.cfm" target="_self">New Student Lists (Fall 2022)</a>
				<br>
				<a class="toolItemLink" href="/chapters/stucur.cfm" target="_self">Student Lists (Winter 2022)</a>
				<br>
				<a class="toolItemLink" href="/email/approvalinterface.cfm" target="_self">Email to Students from Chapter</a>
			</div>
			
		  <div id="brandingResources" class="tool">
				<div class="toolImage" style="background-image:url(images/SailorCosmo.jpg)">
				</div>
				<h3>Branding Resources</h3>
				<a class="toolItemLink" href="/Chapters/downloads.cfm" target="_self">Chapter Media Assets (Downloads)</a>
				<br>
				<a class="toolItemLink" href="/Chapters/T-Shirt-Request-Form.cfm" target="_self">T-Shirt Design Request</a>
			</div>
			
			<div id="swagRequests" class="tool">
				<div class="toolImage" style="background-image:url(images/byuswag.jpg)">
			  </div>
				<h3>Swag Requests</h3>
				<a class="toolItemLink" href="/SwagRequests/studentsendoffform.cfm" target="_self">Student Send-Off</a>
				<br>
				<a class="toolItemLink" href="/SwagRequests/smallgiveawayform.cfm" target="_self">Small Giveaway</a>
				<!---
				<br>
				<a class="toolItemLink" href="/SwagRequests/signedfootballform.cfm" target="_self">Signed Football</a>
				--->
				<br>
				<a class="toolItemLink" href="/SwagRequests/purchasingresources.cfm" target="_self">Purchasing Resources</a>
		  </div>
			
			<div id="requestLists" class="tool">
				<div class="toolImage" style="background-image:url(images/replenishmentgrants.jpg)">
				</div>
				<h3>Request Lists</h3>
				<a class="toolItemLink" href="/RequestLists/AlumniList.cfm" target="_self">Alumni List</a>
				<br>
				<a class="toolItemLink" href="/RequestLists/ReplenishmentGrantRequest.cfm" target="_self">Replenishment Grant Request</a>
			</div>
			
			<div id="chapterTools" class="tool">
				<div class="toolImage" style="background-image:url(images/chaptertools.jpg)">
				</div>
				<h3>Chapter Tools</h3>
				<a class="toolItemLink" href="http://alumni.byu.edu/chapter-pedia" target="_self">ChapterPedia</a>
				<br>
				<a class="toolItemLink" href="/chairs/addresschanges" target="_self">New Moves</a>
				<br>
				<a class="toolItemLink" href="/ChapterReimbursement/RequestForm.cfm" target="_self">Chapter Reimbursement Form Submissions</a>
			</div>
			
			<cf_checkrole role = "ChapterDirectorAdmin">
				<div id="chapterDirectorAdmin" class="tool largeTool">
					<div class="toolImage" style="background-image:url(images/directadmin.jpg)">
					</div>
					<h3>Chapter Director Admin</h3>
					<a class="toolItemLink" href="https://alumni3.byu.edu/adr/chaptercontact.cfm" target="_self">Chapter Chairs</a>
					<br>
					<a class="toolItemLink" href="https://alumni3.byu.edu/adr/chapteronboarding.cfm" target="_self">Chapter Chair Onboarding</a>
				</div>
			</cf_checkrole>
			
			<div id="careers" class="tool largeTool">
				<div class="toolImage" style="background-image:url(images/careers2.jpg)">
				</div>
				<h3>Careers</h3>
				<a class="toolItemLink" href="/admin/top50utah" target="_self">Top 50 Utah Administration</a>
				<br>
				<a class="toolItemLink" href="https://alumni3.byu.edu/admin/connectAdmin" target="_self">BYU Connect (TACTL) Administration</a>
			</div>
			
		</cf_checkRole>
		
		<div id="" class="tool itRecords">
			
			<cf_checkrole role="delegate">
				<span class="itItemLink"><a class="toolItemLink" href="/admin/userAdmin" target="_self">User Administration</a></span>
			</cf_checkrole>
			
			<cf_checkrole role="redirectAdmin">
				<span class="itItemLink"><a class="toolItemLink" href="/admin/redirectAdmin" target="_self">Redirect Administration</a></span>
			</cf_checkrole>
			
			<cf_checkrole role="hinckleyEventAdmin">
				<span class="itItemLink"><a class="toolItemLink" href="/admin/kioskDashboard/site/" target="_self">Kiosk Dashboard</a></span>
			</cf_checkrole>
			
			<cf_checkrole role="chapteradmin">
				<span class="itItemLink"><a class="toolItemLink" href="https://alumni3.byu.edu/watch4cougars/risemanagement.cfm" target="_self">Rise Management</a></span>
			</cf_checkrole>
			
			<span class="itItemLink"><a class="toolItemLink" href="/watch4cougars/" target="_self">Share Your Story Here</a></span>
			
			<!------<span class="itItemLink"><a class="toolItemLink" href="/watch4cougars/risesearch" target="_self">Chapter RISE Search</a></span>---->
			
			<span class="itItemLink"><a class="toolItemLink" href="https://alumni3.byu.edu/mail_chimp/mailchimp_sends.cfm" target="_self">BYU MailChimp - Email Performance</a></span>
			
			<cf_checkrole role="AlumniRelationsManager">
				<span class="itItemLink"><a class="toolItemLink" href="https://alumni3.byu.edu/adr/AEFData.cfm" target="_self">Alumni Engagement Framework - Stats/Data</a></span>
			</cf_checkrole>
			
			<cf_checkrole role="AlumniRelationsManager">
				<span class="itItemLink"><a class="toolItemLink" href="https://alumni3.byu.edu/chapters/chpmanagement.cfm" target="_self">Chapter Definitions</a></span>
				<cfif (#session.netid# eq 'maj72' or  #session.netid# eq 'srmccull' or #session.netid# eq 'mcunning')>
					<span class="itItemLink"><a class="toolItemLink" href="https://alumni3.byu.edu/adr/emailstart.cfm">Email Lists</a></span>
				</cfif>
			</cf_checkrole>
			
			<cfif isdefined("session.netid")>
				<cfquery name="chksession" datasource="alumni-mysql">
					select * from user_auth_proofing
					where (netid = '#trim(session.netid)#')
				</cfquery>
				<cfif #chksession.recordcount# gte 1>
					<span class="itItemLink"><a class="toolItemLink" href="https://alumni3.byu.edu/records/">Alumni Records Management</a></span>
				</cfif>
			</cfif>
			
			<span class="itItemLink"><a class="toolItemLink" href="https://alumni3.byu.edu/adr/byustats.cfm" target="_self">BYU Database Statistics</a></span>
			
			<cf_checkrole role = "chapteradmin">
				<span class="itItemLink"><a class="toolItemLink" href="https://alumni3.byu.edu/adr/requestform.cfm" target="_self">Alumni Data Requests - Tracking Form</a></span>
			</cf_checkrole>
			
			<cf_checkrole role = "global">
				<span class="itItemLink"><a class="toolItemLink" href="/grants" target="_self">Replenishment Grants</a></span>
			</cf_checkrole>
			
			<span class="itItemLink"><a class="toolItemLink" href="/adr/byustats.cfm" target="_self">BYU Alumni Statistics</a></span>
			
			<span class="itItemLink"><a class="toolItemLink" href="https://byu.box.com/s/e9ahg3iw1u2f9h0ee4bisns73rcs6sk9" target="_self">BYU Connect Toolbox</a></span>
			
			<cfif session.netid EQ 'kelliejd' OR session.netid EQ 'nlegakis'>
				<span class="itItemLink"><a class="toolItemLink" href="javascript:downloadFiles();">Replenishment Grant Recipients</a></span>
			</cfif>
			
		</div>
	</div>
</div>

	

<div class="row">
	<a href="/auth/logout/index.cfm?redirect=alumni.byu.edu">
		<button type="button" class="btn btn-byu">
			<span class="glyphicon glyphicon-log-out"></span>&nbsp;&nbsp;Logout
		</button>
	</a>
</div>
	
<script>
	
function downloadFiles() {
	var anchor = document.createElement("a");
	anchor.href = "ADR/files/Rep_Grant_Student_Info.xls";
	anchor.download = "Rep_Grant_Student_Info";
	document.body.appendChild(anchor);
	anchor.click();
	anchor.href = "ADR/files/Rep_Grant_Alternate_Info.xls";
	anchor.download = "Rep_Grant_Alternate_Info";
	anchor.click();
	document.body.removeChild(anchor);
}
	
	
//'var' is deprecated. 'let' triggers a syntax error for some reason.
var date = new Date();
var year = date.getFullYear();
var requestEmailLink = document.getElementById("requestEmailLink");
var link = "/chapterreports/reports/events/index.cfm?year=" + year.toString();
requestEmailLink.href = link;
</script>
	
</section>

<cfinclude template="/template2018/footer.cfm">