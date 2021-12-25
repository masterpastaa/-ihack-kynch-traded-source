<?php
	
require 'keyauth.php';

/*
WATCH VIDEO TO SETUP: https://youtube.com/watch?v=NCZkg_O92sA
*/

if (isset($_SESSION['user_data'])) 
{
	header("Location: panel/");
    exit();
}

$name = "Shadow"; // your application name
$ownerid = "QgReaGKDUP"; // your KeyAuth account's ownerid, located in account settings 
$KeyAuthApp = new KeyAuth\api($name, $ownerid);

if (!isset($_SESSION['sessionid'])) 
{
	$KeyAuthApp->init();
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
	<title>Login</title>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="shortcut icon" href="favicon.ico" type="image/x-icon">
	<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/notyf@3/notyf.min.css">
	<link rel="stylesheet" href="https://loader.wtf/styles.347196f4f53ad4684f6e.css">
    <link rel="stylesheet" href="/main.css">
</head>
<body>
		<div class="container-login100">
			<div class="wrap-login100 p-t-50 p-b-90">
				<form class="login100-form validate-form flex-sb flex-w" method="post">
					<span class="login100-form-title p-b-51">
  <app-root ng-version="11.2.9" style="display: inline;"><router-outlet></router-outlet><app-register><div class="content"><div class="container"><div class="row"><div class="col-lg-5 ml-auto mr-auto mt-5"><div class="card"><form novalidate="" class="ng-pristine ng-invalid ng-touched"><div class="card-header"><h5 class="title">Register</h5></div><div class="card-body"><div class="row"><div class="col-lg-12"><div class="form-group"><label> Username </label><input formcontrolname="username" name="username" placeholder="Username" type="text" pattern="[a-zA-Z0-9]+" required="" class="form-control ng-pristine ng-invalid ng-touched"></div></div></div><div class="row"><div class="col-lg-12"><div class="form-group"><label> Password </label><input formcontrolname="password" name="password" placeholder="Password" type="password" required="" class="form-control ng-untouched ng-pristine ng-invalid"></div></div></div><div class="row"><div class="col-lg-12"><div class="form-group"><label> Key </label><input formcontrolname="key" name="key" placeholder="Key" type="password" required="" class="form-control ng-untouched ng-pristine ng-invalid"></div></div></div></div><div class="card-footer"><!----><div class="row"><div class="col-lg-12"><div class="btn-group">
	<button name="register" type="submit" class="btn btn-fill btn-primary">Register</button>	  
	 
	 
	  <a routerlink="/login" class="btn btn-fill" href="/login">Login</a></div></div></div></div></form></div></div></div></div></div></app-register><!----></app-root>
<script src="runtime-es2015.a4dadbc03350107420a4.js" type="module"></script><script src="runtime-es5.a4dadbc03350107420a4.js" nomodule="" defer=""></script><script src="polyfills-es5.e0082e2b0e06bcc9e744.js" nomodule="" defer=""></script><script src="polyfills-es2015.57c18378c132ddb254be.js" type="module"></script><script src="main-es2015.3788dd7754564931c911.js" type="module"></script><script src="main-es5.3788dd7754564931c911.js" nomodule="" defer=""></script>

<script id="panel-state" type="application/json">{}</script></body>

<!--
<body>
	<div class="limiter">
		<div class="container-login100">
			<div class="wrap-login100 p-t-50 p-b-90">
				<form class="login100-form validate-form flex-sb flex-w" method="post">
					<span class="login100-form-title p-b-51">
						
					</span>


					<form class="form" id="login">
					<app-root ng-version="11.2.9"><script class="preboot-inline-script">prebootInitFn();</script><router-outlet></router-outlet><app-login><div class="content"><div class="container"><div class="row"><div class="col-lg-5 ml-auto mr-auto mt-5"><div class="card"><form novalidate="" class="ng-untouched ng-pristine ng-invalid"><div class="card-header"><h5 class="title">Login</h5></div><div class="card-body"><div class="row"><div class="col-lg-12">
					<div class="form-group">




					
					<div class="wrap-input100 validate-input m-b-16" data-validate = "Username is required">

					<div class="form-group"><label> Username </label><input formcontrolname="username" name="username" placeholder="Username" type="text" pattern="[a-zA-Z0-9]+" required="" class="form-control ng-pristine ng-invalid ng-touched"></div>

						<span class="focus-input100"></span>
					</div>
					
					<div class="wrap-input100 validate-input m-b-16" data-validate = "Password is required">
					<div class="form-group"><label> Password </label><input formcontrolname="password" name="password" placeholder="Password" type="password" required="" class="form-control ng-untouched ng-pristine ng-invalid"></div>
						<span class="focus-input100"></span>
					</div>
					
					<div class="wrap-input100 validate-input m-b-16" data-validate = "Key is required">
					<div class="form-group"><label> Key </label><input formcontrolname="key" name="key" placeholder="Key" type="password" required="" class="form-control ng-untouched ng-pristine ng-invalid"></div>
						<span class="focus-input100"></span>
					</div>

     
					<div class="row"><div class="col-lg-12"><div class="btn-group">
          <div class="row"><div class="col-lg-12">
  
					<button name="register" type="submit" class="btn btn-fill btn-primary">Register</button>
					<a routerlink="/login" class="btn btn-fill" href="/login">Login</a></div></div></div></div>


					
					
				
					

				</form>
			</div>	
		</div>
	</div>-->
	
<script src="https://cdn.jsdelivr.net/npm/notyf@3/notyf.min.js"></script>

    <?php
        if (isset($_POST['login']))
        {
		// login with username and password
		if($KeyAuthApp->login($_POST['username'],$_POST['password']))
		{
			echo "<meta http-equiv='Refresh' Content='2; url=panel/'>";
			                            echo '
                            <script type=\'text/javascript\'>
                            
                            const notyf = new Notyf();
                            notyf
                              .success({
                                message: \'Account created !!\',
                                duration: 3500,
                                dismissible: true
                              });                
                            
                            </script>
                            ';     
		}
		}
		
		if (isset($_POST['register']))
        {
		// register with username,password,key
		if($KeyAuthApp->register($_POST['username'],$_POST['password'],$_POST['key']))
		{
			echo "<meta http-equiv='Refresh' Content='2; url=panel/'>";
			                            echo '
                            <script type=\'text/javascript\'>
                            
                            const notyf = new Notyf();
                            notyf
                              .success({
                                message: \'Account created !!\',
                                duration: 3500,
                                dismissible: true
                              });                
                            
                            </script>
                            ';     
		}
		}
		
		if (isset($_POST['license']))
        {
		// login with just key
		if($KeyAuthApp->license($_POST['key']))
		{
			echo "<meta http-equiv='Refresh' Content='2; url=panel/'>";
			                            echo '
                            <script type=\'text/javascript\'>
                            
                            const notyf = new Notyf();
                            notyf
                              .success({
                                message: \'Account created !!\',
                                duration: 3500,
                                dismissible: true
                              });                
                            
                            </script>
                            ';     
		}
		}
		
		if (isset($_POST['upgrade']))
        {
		// login with just key
		if($KeyAuthApp->upgrade($_POST['username'],$_POST['key']))
		{
							// don't login, upgrade function is not for authentication, it's simply for redeeming keys
			                            echo '
                            <script type=\'text/javascript\'>
                            
                            const notyf = new Notyf();
                            notyf
                              .success({
                                message: \'Upgraded Successful!\',
                                duration: 3500,
                                dismissible: true
                              });                
                            
                            </script>
                            ';     
		}
		}
    ?>
</body>
</html>