<?php
	
require 'keyauth.php';

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
					<label> Username </label><input type="text" name="username" placeholder="Username" class="form-control ng-untouched ng-pristine ng-invalid"></div></div></div>
						<span class="focus-input100"></span>
					</div>
					
					<div class="wrap-input100 validate-input m-b-16" data-validate = "Password is required">
					<div class="row"><div class="col-lg-12">
                    <div class="form-group">
                    <label> Password </label><input type="password" name="password" placeholder="Password" class="form-control ng-untouched ng-pristine ng-invalid"></div></div></div>
						<span class="focus-input100"></span>
					</div>
					
					<div class="row"><div class="col-lg-12">
      </div></div></div><div class="card-footer"><div class="row"><div class="col-lg-12"><div class="btn-group">
          <div class="row"><div class="col-lg-12">
<div class="form__message form__message--error"></div>     

					<div class="container-login100-form-btn m-t-17">
					<div class="btn-group">
					<input type="submit" name="login" value="Login" class="btn btn-fill btn-primary">
						
						
						
						<a routerlink="/register" class="btn btn-fill" href="/register">Register</a></div>   

					</div>
					
					
					
					
					
					

				</form>
			</div>	
		</div>
	</div>
	
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
                                message: \'You are logged in!\',
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
                                message: \'You have successfully logged in!\',
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
                                message: \'You have successfully logged in!\',
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